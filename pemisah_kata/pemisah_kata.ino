String kataPublish="/mode:publish/data:(pres:2345,ki:23,kp=123,kd:12412)/asal:nodeSensor/channel:1234/";
String kataSubcribe="/mode:subcribe/data:(pres,ki,kp,kd,dp)/asal:nodeMaster/channel:1234/";
int channel=1234;
String mode[]={"publish","subcribe"};
String data[]={"pres","ki","kp","kd"};
String dataNameValue[]={"pres","ki","kp","kd","dp"};
String asal[]={"nodeMaster","nodeSensor"};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pisahData(kataPublish);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void pisahData(String data){
  int index=data.indexOf("/data:");
  int index1=data.indexOf("/",index+1);
  String hasil=data.substring(index,index1);
  Serial.println(hasil);
  
}
