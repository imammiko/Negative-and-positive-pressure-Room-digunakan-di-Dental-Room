class NrfKom: public RF24 {
  public:
    NrfKom(const uint64_t pipe[2], int pin1, int pin2, String channel, String nodeAsal[]);
    void deklarasi();
    void pipeChange(String change);// mengubah pipe

    int lihat();

    //================data masuk
    //void pemisah(String data);//belum digutnakan

    void menerima();// menerima data dari transmit
    //======================data kirim_
    void mengirim(String data);// mengirim dari transmitt
    void merakit(String dataObjek, String objekNilai[], int nilai[], int banyakNilai);// merakit data bentuk data
    String dataGabungHeader(String data, int paketData, int randomData);// menggabungkan header
    byte dataGotbyteKirim = 0; // data mengirim variable
    byte completeKirim = 1;//data kompltere dari kirim
    int randomKirim = 0;// random dari kirim
    //=========================variable
    const uint64_t _pipes[2];
    byte counter = 1;// penjumlahan dari example
    String channel = "";//chaneel node
    String node[3];//node yang ada
    String modeData[2] = {"subcribe", "publish"};//subcribe mode pengiriman
    //=============data obj di terima
    int statusPipe = 0;// status pipe membantu change nrf
    byte randomData = 0;// random data pada menrima

    //================RR di terima
    int randomValue = 0;//data yang diterima random value sebelum nya
    int packetValue = 0;//data yang packet diterima value sebelumnya
    byte complete = 1;// status complete data
    String dataKumpul = "";//mengumpulkan data
  String dataObjek[5] = {"/rd:", "/md:", "/dt:", "/sl:", "/chnl:"};

  private:
  
};



NrfKom::NrfKom(const uint64_t pipe[2], int pin1, int pin2, String Channel, String nodeAsal[]): RF24(pin1, pin2) {
  memcpy (_pipes, pipe,  sizeof(const uint64_t) * 2);
  memcpy (node, nodeAsal ,  sizeof(String) * 3);
  channel = Channel;

  // Serial.println(_pipes[0] );
}
int NrfKom::lihat() {
  return _pipes[0];
}

void NrfKom::deklarasi() {

  begin();
  setAutoAck(1);                    // Ensure autoACK is enabled
  enableAckPayload();               // Allow optional ack payloads
  enableDynamicPayloads();

  startListening();                 // Start listening
  printDetails();
  setPALevel(RF24_PA_MAX);
}
//"r12p0!/md:publish/dt:(sensor:2345,ki:23,kp=123,kd:12412)/sl:nodeSensor/chnl:billy/>";
void NrfKom::merakit(String dataObjek, String objekNilai[], int nilai[], int banyakNilai) {

  String data = "";

  if (dataObjek = "publish") {
    //    data.concat("R");
    //    data.concat(randomData);
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
    data.concat(node[0]);
    data.concat(this->dataObjek[4]);
    data.concat(channel);
    data.concat("/");
    data.concat(">");
    //data.concat();

  }
  // int x=sizeof(objekNilai) / sizeof(*objekNilai);
  //Serial.println(data);
//==============================
  
  float jumlahDataDibagi = 0;
  
  String dataGotbyte = "";

  jumlahDataDibagi = (float)data.length() / 26.0;
  jumlahDataDibagi = ceil(jumlahDataDibagi);
  randomKirim = random(10, 99);
  if (completeKirim == 1) {
    
    
    dataGotbyte = String(dataGotbyteKirim);
    for (int i = 0; i <= jumlahDataDibagi; i++) {
      if (dataGotbyte == "100" || completeKirim==1) {
        completeKirim = 0;
        i = 0;
        mengirim(dataGabungHeader(data, i, randomKirim));
      } else if (dataGotbyte.substring(0, 2) == "10") {
       i=(dataGotbyte.substring(2,3)).toInt();
       mengirim(dataGabungHeader(data, i, randomKirim));
      }else if (dataGotbyte.substring(0, 2) == "11") {
       i=(dataGotbyte.substring(2,3)).toInt();
       mengirim(dataGabungHeader(data, i, randomKirim));
      }


      
    }
    completeKirim = 1;
    dataGotbyteKirim = 0;
  }

  //===============================================================
// this->mengirim(dataGabungHeader(data, 0,85 ));
//this->mengirim(data);
}
String NrfKom::dataGabungHeader(String data, int paketData, int randomData) {
  String Data = data;
  String dataHeader = "";
  float jumlahDataDibagi = 0;
  String DataPotong = "";
  jumlahDataDibagi = (float)Data.length() / 26.0;
  jumlahDataDibagi = ceil(jumlahDataDibagi);
  jumlahDataDibagi = floor((float)Data.length() / jumlahDataDibagi);
  DataPotong = Data.substring(jumlahDataDibagi * paketData, int(jumlahDataDibagi) * (paketData + 1));
  dataHeader.concat("R");
  dataHeader.concat(randomData);
  dataHeader.concat("P");
  dataHeader.concat(paketData);
  dataHeader.concat("!");
  Data = dataHeader + DataPotong;
  return Data;
}

void NrfKom::mengirim(String data) {
  String Data = "";
  Data = data;

  Serial.println(Data);
  pipeChange("transmitter");
  //
  //  printf("Now sending %d as payload. ", counter);
  byte gotByte=0;
  char text[32] = "";
  Data.toCharArray(text, 32);
  //  Serial.println(text);
  unsigned long time = micros();

  if (! write(&text, sizeof(text))) {
    Serial.println(F("failed."));
  } else {
    if (! available()) {
      Serial.println(F("Blank Payload Received."));
    } else {
      while (isAckPayloadAvailable()) {
        gotByte=0;
        unsigned long tim = micros();
        read(&gotByte, 1);
        dataGotbyteKirim = gotByte;
         
        Serial.println(gotByte);
       // printf("Got response %d, round-trip delay: %lu microseconds\n\r", gotByte, tim - time);
        
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
  pipeChange("reciver");
  byte pipeNo;
  char gotByte[200] = "";
  byte text = 1; // Dump the payloads until we've gotten everything
  while (available(&pipeNo)) {
    read(&gotByte, sizeof(gotByte));
    terima = gotByte;
    Serial.println(terima);
    if (terima.indexOf("!") > -1) {
      header = terima.substring(0, terima.indexOf("!") + 1);
    } else {
      text=0;
      text = 210;
      writeAckPayload(pipeNo, &text, 1);
    }
    if (header.indexOf("R") > -1 && header.indexOf("P") > -1 && header.indexOf("P") > header.indexOf("R")) {
      RString = header.substring(header.indexOf("R") + 1, header.indexOf("P"));
      PString = header.substring(header.indexOf("P") + 1, header.indexOf("!"));
      P = PString.toInt();
      R = RString.toInt();


      //======================pertama
      if (complete == 1 && P == 0) {
        randomValue = R;
        text=0;
        text =  0;// sudah masuk dengan baik
        writeAckPayload(pipeNo, &text, 1);
        complete = 0;
        //ambil data
        dataKumpul += terima.substring(header.indexOf("!") + 1);
        if (terima.indexOf(">") > -1) {
          complete = 1;// data sudah komplit
          packetValue = 0;
        }
        packetValue += 1;
        //==
      } else if (complete == 1 && P > 0) {
        text=0;
        text = 100;//random benar data berlebihan satu
        writeAckPayload(pipeNo, &text, 1);
      }
      //**************************pertama

      //============data dikirim double========



      //*****************double*****************

      //==========================kedua
      if (complete == 0 && randomValue == R ) {//check paket ini lanjutan data
        if (packetValue == P) {
          packetValue += 1;//count p ditambah
          dataKumpul += terima.substring(header.indexOf("!") + 1);
          if (terima.indexOf(">") > -1) {
            complete = 1;
            packetValue = 0;
          }
          text = 0;//random benar data berlebihan satu
          writeAckPayload(pipeNo, &text, 1);
        } else if (packetValue != P) {// p tidak sama yang diminta
          Serial.print("tidak ada sama:");
          if (packetValue < P) {
            Serial.println(packetValue);
            text=0;
            text = 100 + packetValue; //random benar data berlebihan satu
            writeAckPayload(pipeNo, &text, 1);
          } else {
            Serial.println(packetValue);
            text=0;
            text = 110 + packetValue; //random benar data kurang satu
            writeAckPayload(pipeNo, &text, 1);
          }

        }

      } if (randomValue != R) {
        complete = 1;
        dataKumpul = "";
      }



      //********************kedua

     // Serial.println(dataKumpul);
    } else {// data tidak di ketahui

      text = 210;
      writeAckPayload(pipeNo, &text, 1);
      break;
    }

  }
}



//=============




void NrfKom::pipeChange(String change) {
  if (statusPipe != 1 && change == "transmitter" ) { //transmitter
    statusPipe = 1;
    openWritingPipe(_pipes[0]);
    openReadingPipe(1, _pipes[1]);
    stopListening();
  } else if (statusPipe != 2 && change == "reciver") { //reciver
    statusPipe = 2;
    openWritingPipe(_pipes[1]);
    openReadingPipe(1, _pipes[0]);
    startListening();
  } else {
    // Serial.print("perubahan pipe gagal  ");
  }
}
