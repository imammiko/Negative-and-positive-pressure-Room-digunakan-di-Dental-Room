class NrfKom: public RF24 {
  public:
    NrfKom(const uint64_t pipe[2], int pin1, int pin2, String channel, String nodeAsal[]);
    void deklarasi();


    int lihat();

    //================data masuk
    void pemisah(String data);
    String segment(String objek, String data);
    void menerima();
    //======================data kirim_
    void mengirim(String data);
    void merakit(String dataObjek, String objekNilai[], int nilai[], int banyakNilai);
    void dataGabungHeader();

    //=========================variable
    const uint64_t _pipes[2];
    byte counter = 1;
    byte counterPaket = 0;
    String channel = "";
    String node[3];
    String modeData[2] = {"subcribe", "publish"};
    //=============data obj
    int statusPipe = 0;
    byte counterRandom = 0;
    byte randomData = 0;
    void pipeChange(String change);
    //================RR
    int randomValue = 0;
    int packetValue = 0;
    byte complete = 1;
    String dataKumpul = "";
    void ambilData(String Data);
    int countP = 0;
  private:
    String dataObjek[5] = {"/rd:", "/md:", "/dt:", "/sl:", "/chnl:"};
};



NrfKom::NrfKom(const uint64_t pipe[2], int pin1, int pin2, String channel, String nodeAsal[]): RF24(pin1, pin2) {
  memcpy (this->_pipes, pipe,  sizeof(const uint64_t) * 2);
  memcpy (this->node, nodeAsal ,  sizeof(String) * 3);
  this->channel = channel;

  // Serial.println(_pipes[0] );
}
int NrfKom::lihat() {
  return _pipes[0];
}

void NrfKom::deklarasi() {

  this->begin();
  this->setAutoAck(1);                    // Ensure autoACK is enabled
  this->enableAckPayload();               // Allow optional ack payloads
  this->enableDynamicPayloads();
  // this->setRetries(0, 15);                // Smallest time between retries, max no. of retries
  //radio.setPayloadSize(1);                // Here we are sending 1-byte payloads to test the call-response speed
  // radio.openWritingPipe(pipes[1]);        // Both radios listen on the same pipes by default, and switch when writing
  // radio.openReadingPipe(1, pipes[0]);
  this->startListening();                 // Start listening
  this->printDetails();
  this->setPALevel(RF24_PA_MAX);
}
//"r12p0!/md:publish/dt:(sensor:2345,ki:23,kp=123,kd:12412)/sl:nodeSensor/chnl:billy/>";
void NrfKom::merakit(String dataObjek, String objekNilai[], int nilai[], int banyakNilai) {

  String data = "";

  if (dataObjek = "publish") {
    //    data.concat("R");
    //    data.concat(this->randomData);
    //    data.concat("P");
    data.concat(this->dataObjek[1]);
    data.concat(dataObjek);
    data.concat(this->dataObjek[2]);
    data.concat("(");
    for (int x = 0; x < banyakNilai; x++) {
      data.concat(objekNilai[x]);
      data.concat(":");
      data.concat(nilai[x]);
      if (x < banyakNilai - 1) {
        data.concat(",");
      }
    }
    data.concat(")");
    data.concat(this->dataObjek[3]);
    data.concat(this->node[0]);
    data.concat(this->dataObjek[4]);
    data.concat(this->channel);
    data.concat("/");
    data.concat(">");
    //data.concat();

  };
  // int x=sizeof(objekNilai) / sizeof(*objekNilai);
  //Serial.println(data);
  mengirim(data);
}
  void NrfKom::dataGabungHeader(){
    
    }

void NrfKom::mengirim(String data) {
  //  this->openWritingPipe(this->_pipes[0]);
  //  this->openReadingPipe(0, this->_pipes[1]);
  //  this->stopListening();
  //  char text[100] = "";
  //  data.toCharArray(text, 100);
  //  this->write(&text, sizeof(text));
  //  delay(1000);
  //  Serial.println(text);
  String Data = data;
  String DataPotong = "";
  String dataHeader = "";
  float jumlahDataDibagi = 0;
  int lastData = 0;
  int nowData = 0;
  int lastP = 0;
  int nowP = 0;
  if (counterRandom == 0) {
    this->randomData = random(10, 99);
    counterRandom += 1;
  }
  jumlahDataDibagi = (float)Data.length() / 26.0;
  jumlahDataDibagi = ceil(jumlahDataDibagi);
  jumlahDataDibagi = floor((float)Data.length() / jumlahDataDibagi);
  DataPotong = Data.substring(0, int(jumlahDataDibagi));
  dataHeader.concat("R");
  dataHeader.concat(this->randomData);
  dataHeader.concat("P");
  dataHeader.concat(this->counterPaket);
  dataHeader.concat("!");
  Data = dataHeader + DataPotong;
  //  jumlahDataDibagi=Data.length()/32;
  //  jumlahDataDibagi=ceil(jumlahDataDibagi);
  //  jumlahDataDibagi=Data.length()/jumlahDataDibagi;
  //  DataPotong=Data.substring(0,jumlahDataDibagi);
  // lastData=jumlahDataDibagi+lastData;

  this->pipeChange("transmitter");
  //
  //  printf("Now sending %d as payload. ", counter);
  byte gotByte;
  char text[32] = "";
  Data.toCharArray(text, 32);
  //  Serial.println(text);
  unsigned long time = micros();                          // Take the time, and send it.  This will block until complete
  //  //Called when STANDBY-I mode is engaged (User is finished sending)
  if (! this->write(&text, sizeof(text))) {
    Serial.println(F("failed."));
  } else {
    if (! this->available()) {
      Serial.println(F("Blank Payload Received."));
    } else {
      while ( this->available()) {
        unsigned long tim = micros();
        this->read(&gotByte, 1);
        printf("Got response %d, round-trip delay: %lu microseconds\n\r", gotByte, tim - time);
        counter++;
      }
    }
  }
}
//"r12p0!/md:publish/dt:(sensor:2345,ki:23,kp=123,kd:12412)/sl:nodeSensor/chnl:billy/>";
void NrfKom::menerima() {
  String terima = "";
  String header = "";
  //int x=0;
  String RString = "";
  String PString = "";
  int R = 0;
  int P = 0;
  this->pipeChange("reciver");
  byte pipeNo;
  char gotByte[200] = "";
  byte text = 1; // Dump the payloads until we've gotten everything
  while (this->available(&pipeNo)) {
    this->read(&gotByte, sizeof(gotByte));
    terima = gotByte;
    if (terima.indexOf("!") > -1) {
      header = terima.substring(0, terima.indexOf("!") + 1);
    } else {
      text = 210;
      this->writeAckPayload(pipeNo, &text, 1);
    }
    if (header.indexOf("R") > -1 && header.indexOf("P") > -1 && header.indexOf("P") > header.indexOf("R")) {
      RString = header.substring(header.indexOf("R") + 1, header.indexOf("P"));
      PString = header.substring(header.indexOf("P") + 1, header.indexOf("!"));
      P = PString.toInt();
      R = RString.toInt();


      //======================pertama
      if (complete == 1 && P == 0) {
        this->randomValue = R;
        text =  0;// sudah masuk dengan baik
        this->writeAckPayload(pipeNo, &text, 1);
        complete = 0;
        //ambil data
        dataKumpul += terima.substring(header.indexOf("!") + 1);
        if (terima.indexOf(">") > -1) {
          complete = 1;// data sudah komplit
          this->countP = 0;
        }
        this->countP += 1;
        //==
      } else if (complete == 1 && P > 0) {
        text = 100;//random benar data berlebihan satu
        this->writeAckPayload(pipeNo, &text, 1);
      }
      //**************************pertama

      //============data dikirim double========
      if(R ==this->randomValue && P==this->packetValue){
          text = 0;//random benar data berlebihan satu
        this->writeAckPayload(pipeNo, &text, 1);
        }


      //*****************double*****************

      //==========================kedua
      if (complete == 0 && this->randomValue == R) {//check paket ini lanjutan data
        if (this->countP == P) {
          this->countP += 1;//count p ditambah
          dataKumpul += terima.substring(header.indexOf("!") + 1);
          if (terima.indexOf(">") > -1) {
            complete = 1;
            this->countP = 0;
          }
        } else if (this->countP != P) {// p tidak sama yang diminta
          if (this->countP > P) {
            text = 100 + this->countP; //random benar data berlebihan satu
            this->writeAckPayload(pipeNo, &text, 1);
          } else {
            text = 110 + this->countP; //random benar data berlebihan satu
            this->writeAckPayload(pipeNo, &text, 1);
          }

        }

      }


      //********************kedua
      //this->randomValue = R;

    } else {// data tidak di ketahui
      text = 210;
      this->writeAckPayload(pipeNo, &text, 1);
      break;
    }
    Serial.println(dataKumpul);
  }
}



//=============
void NrfKom::pemisah(String data) {
  String penampungData = data;
  if (this->segment(dataObjek[4], data) == this->channel) {
    Serial.println(this->segment(dataObjek[4], data));
  }


}

String NrfKom::segment(String objek, String data) {
  String penampungData = data;
  String hasil =
    penampungData.substring(
      penampungData.indexOf(":", penampungData.indexOf(objek) + 1) + 1,
      penampungData.indexOf("/", penampungData.indexOf(objek) + 1)

    );
  return hasil;
}

void NrfKom::pipeChange(String change) {
  if (this->statusPipe != 1 && change == "transmitter" ) { //transmitter
    statusPipe = 1;
    this->openWritingPipe(this->_pipes[0]);
    this->openReadingPipe(1, this-> _pipes[1]);
    this->stopListening();
  } else if (statusPipe != 2 && change == "reciver") { //reciver
    this->statusPipe = 2;
    this->openWritingPipe(this->_pipes[1]);
    this->openReadingPipe(1, this->_pipes[0]);
    this->startListening();
  } else {
    // Serial.print("perubahan pipe gagal  ");
  }
}
