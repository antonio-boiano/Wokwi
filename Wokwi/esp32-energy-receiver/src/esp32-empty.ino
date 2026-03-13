#include <esp_now.h>
#include <WiFi.h>

#include <esp_mac.h>  // Required for esp_read_mac()

void print_mac() {  
    uint8_t mac[6];
    
    // Get the factory-set MAC address for the Wi-Fi station (ESP-NOW works in STA mode)
    esp_read_mac(mac, ESP_MAC_WIFI_STA);

    Serial.print("Wi-Fi Station MAC: ");
    Serial.printf("%02X:%02X:%02X:%02X:%02X:%02X\n",
                  mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}



void print_data(const uint8_t *data, int len){
  char receivedString[len];  // +1 for null terminator
  memcpy(receivedString, data, len);

  // Convert the char array to a String
  String receivedMessage = String(receivedString);

  Serial.print("Received Message: ");
  Serial.println(receivedMessage);
}

// MAC receiver
//C8:C9:A3:C6:0D:78
uint8_t broadcastAddress[] = {0x8C, 0x9C, 0x3A, 0x6C, 0xD0, 0x87}; //1

esp_now_peer_info_t peerInfo;


void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Ok" : "Error");
}

//Receiving Callback
void OnDataRecv(const esp_now_recv_info *info, const uint8_t *data, int len) {
  //memcpy(tr, incomingData, sizeof(tr));
  Serial.print("Bytes received: ");
  Serial.println(len);
  print_data(data,len);

}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //send callback
  esp_now_register_send_cb(OnDataSent);
  //receive callback
  esp_now_register_recv_cb(OnDataRecv);
  
  // Peer Registration
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  print_mac();

}
void loop() {
  delay(1000);
  Serial.println("Waiting for a Message");

}