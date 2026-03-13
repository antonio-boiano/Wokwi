#include <esp_now.h>
#include <WiFi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"


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
uint8_t broadcastAddress[] = {0xC8, 0xC9, 0xA3, 0xD0, 0xF5, 0xA8}; //1


esp_now_peer_info_t peerInfo;

// Sending callback
/* esp_now_send(uint8_t *da, uint8_t *data, uint8_t *len)
   Parameters:
     uint8_t *da: array of the MAC address of the peer to which the data packet is sent. If the address is NULL, the data is sent to all addresses in the Communication Table.
     uint8_t *data: array with the data packet to be sent.
     uint8_t len: length of the array of the data packet.
*/

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
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
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
/* Add peer 
   esp_now_add_peer(uint8_t *mac_addr, uint8_t role, uint8_t channel, uint8_t *key, uint8_t key_len)
   Parameters:
         uint8_t *mac_addr: array of the MAC address of the communication peer.
         uint8_t role: role of the communication peer (0=idle, 1=master, 2=slave, and 3=master + slave).
         uint8_t channel: communication channel, usually from 1 to 13 (some regions may use channel 14).
         uint8_t *key: array of 16 bytes with the communication key. NULL indicates no key.
         uint8_t key_len: length of the communication key. It must currently be 16 bytes.
*/

  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

}
void loop() {
  String pp="Hello!!Hello!!Hello!!Hello!!Hello!!Hello!!Hello!!Hello!!Hello!!Hello!!Hello!!Hello!!Hello!!Hello!!Hello!!Hello!!Hello!!Hello!!Hello!!Hello!!Hello!!Hello!!Hello!!Hello!!Hello!!Hello!!Hello!!";

  WiFi.setTxPower(WIFI_POWER_2dBm);
  esp_now_send(broadcastAddress, (uint8_t*)pp.c_str(), pp.length() + 1);

  delay(500);

  WiFi.setTxPower(WIFI_POWER_19_5dBm);
  esp_now_send(broadcastAddress, (uint8_t*)pp.c_str(), pp.length() + 1);

  delay(2000);
}