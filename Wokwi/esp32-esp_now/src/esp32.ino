#include <WiFi.h>
#include <esp_now.h>

// MAC receiver
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

esp_now_peer_info_t peerInfo;

// Sending callback
void OnDataSent(const wifi_tx_info_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Ok" : "Error");
}

//Receiving Callback
void OnDataRecv(const esp_now_recv_info_t * mac, const uint8_t *data, int len) {
  Serial.print("Message received: ");
  char receivedString[len];
  memcpy(receivedString, data, len);
  Serial.println(String(receivedString));
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  esp_now_init();
  //send callback
  esp_now_register_send_cb(OnDataSent);
  //receive callback
  esp_now_register_recv_cb(OnDataRecv);

  // Peer Registration
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  // Add peer (Is possible to register multiple peers)
  esp_now_add_peer(&peerInfo);
}

void loop() {
  while (!Serial.available()); // Wait for input
  String message = Serial.readStringUntil('\n');
/* esp_now_send(uint8_t *da, uint8_t *data, uint8_t *len)
   Parameters:
     uint8_t *da: array of the MAC address of the peer to which the data packet is sent.
                  If the address is NULL, the data is sent to all addresses in the Communication Table (all the registered peers).
     uint8_t *data: array with the data packet to be sent.
     uint8_t len: length of the array of the data packet.
*/
  esp_now_send(broadcastAddress, (uint8_t*)message.c_str(), message.length() + 1);
}



