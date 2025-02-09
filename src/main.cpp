
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "esp_bt_device.h"
#include "esp_bt_main.h"
#include "esp_gatt_common_api.h"

// Define BLE Service and Characteristic UUIDs
#define SERVICE_UUID        "12345678-1234-1234-1234-123456789abc"
#define COMMAND_CHAR_UUID   "abcd1234-5678-90ab-cdef-1234567890ab"  // Write request characteristic
#define RESPONSE_CHAR_UUID  "dcba4321-8765-09ba-fedc-0987654321ba"  // Notify response characteristic

BLECharacteristic *responseCharacteristic;

// std::string responseText = "The United States of America (USA), commonly known as the United States (U.S.) or America, is a country primarily located in North America. It is a federal union of 50 states and Washington, D.C., its federal capital district. The 48 contiguous states border Canada to the north and Mexico to the south, with the semi-exclavic state of Alaska in the northwest and the archipelagic state of Hawaii in the Pacific Ocean. The U.S. also asserts sovereignty over five major island territories and various uninhabited islands. The country has the world's third-largest land area and third-largest population, exceeding 340 million. The country also possesses the world's second-largest exclusive economic zone. Its three largest metropolitan areas are New York, Los Angeles, and Chicago, and its three most populous states are California, Texas, and Florida.";  
// std::string responseText = "The United States of America (USA), commonly known as the United States (U.S.) or America, is a country primarily located in North America. It is a federal union of 50 states and Washington, D.C., its federal capital district. The 48 contiguous states border Canada to the north and Mexico to the south, with the semi-exclavic state of Alaska in the northwest and the archipelagic state of Hawaii in the Pacific Ocean. The U.S. also asserts sovereignty over five major island territories and various uninhabited islands.[j] The country has the world's third-largest land area[d] and third-largest population, exceeding 340 million.[k] The country also possesses the world's second-largest exclusive eThe United States of America (USA), commonly known as the United States (U.S.) or America, is a country primarily located in North America. It is a federal union of 50 states and Washington, D.C., its federal capital district. The 48 contiguous states border Canada to the north and Mexico to the south, with the semi-exclavic state of Alaska in the northwest and the archipelagic state of Hawaii in the Pacific Ocean. The U.S. also asserts sovereignty over five major island territories and various uninhabited islands.[j] The country has the world's third-largest land area[d] and third-largest population, exceeding 340 million.[k] The country also possesses the world's second-largest exclusive economic zone. Its three largest metropolitan areas are New York, Los Angeles, and Chicago, and its three most populous states are California, Texas, and Florida.Paleo-Indians migrated to North America across the Bering land bridge more than 12,000 years ago, and formed various civilizations and societies. Spanish exploration and colonization led to the establishment in 1513 of Spanish Florida, the first European colony in what is now the continental United States. Early French colonization failed, and major settlements came much later. Subsequent British colonization led to the first settlement of the Thirteen Colonies in Virginia in 1607. The development of intensive agriculture in the rapidly expanding colonies soon led to the forced migration of enslaved Africans. Clashes with the British Crown over taxation and political representation sparked the American Revolution, with the Second Continental Congress formally declaring independence on July 4, 1776. Following its victory in the 1775–1783 Revolutionary War, the country continued to expand westward across North America, resulting in the dispossession of native inhabitants. As more states were admitted,[l] a North–South division over slavery led to the secession of the Confederate States of America, which fought the Union in the 1861–1865 American Civil War. With the victory and preservation of the United States, slavery was abolished nationally. By 1900, the country had established itself as a great power, a status solidified after its involvement in World War I. After Japan's attack on Pearl Harbor in December 1941, the U.S. entered World War II. Its aftermath left the U.S. and the Soviet Union as the world's two superpowers and led to the Cold War, during which both countries struggled for ideological dominance and international influence. Following the Soviet Union's collapse and the end of the Cold War in 1991, the U.S. emerged as the world's sole superpower, wielding significant geopolitical influence globally. The U.S. national government is a presidential constitutional federal republic and liberal democracy with three separate branches: legislative, executive, and judicial. It has a bicameral national legislature composed of the House of Representatives, a lower house based on population, and the Senate, an upper house based on equal representation for each state. The country's Democratic and Republican parties have dominated American politics since the 1850s. Federalism provides substantial autonomy to the 50 states, while American values are based on a democratic political tradition that draws its inspiration from the European Enlightenment movement. One of the world's most developed countries, the United States accounted for over a quarter of nominal global economic output in 2024, and its economy has been the largest by nominal GDP since about 1890. It possesses by far the largest amount of wealth of any country and has the highest disposable household income per capita among OECD countries, though U.S. wealth inequality is higher than in most other developed countries. The U.S. ranks among the world's highest in economic competitiveness, productivity, innovation, human rights, and higher education. Its hard power and American cultural influence have a global reach. The U.S. is a founding member of the World Bank, the Organization of American States, NATO, the G7, and the United Nations,[m] as well as a permanent member of the UN Security Council.conomic zone. Its three largest metropolitan areas are New York, Los Angeles, and Chicago, and its three most populous states are California, Texas, and Florida.Paleo-Indians migrated to North America across the Bering land bridge more than 12,000 years ago, and formed various civilizations and societies. Spanish exploration and colonization led to the establishment in 1513 of Spanish Florida, the first European colony in what is now the continental United States. Early French colonization failed, and major settlements came much later. Subsequent British colonization led to the first settlement of the Thirteen Colonies in Virginia in 1607. The development of intensive agriculture in the rapidly expanding colonies soon led to the forced migration of enslaved Africans. Clashes with the British Crown over taxation and political representation sparked the American Revolution, with the Second Continental Congress formally declaring independence on July 4, 1776. Following its victory in the 1775–1783 Revolutionary War, the country continued to expand westward across North America, resulting in the dispossession of native inhabitants. As more states were admitted,[l] a North–South division over slavery led to the secession of the Confederate States of America, which fought the Union in the 1861–1865 American Civil War. With the victory and preservation of the United States, slavery was abolished nationally. By 1900, the country had established itself as a great power, a status solidified after its involvement in World War I. After Japan's attack on Pearl Harbor in December 1941, the U.S. entered World War II. Its aftermath left the U.S. and the Soviet Union as the world's two superpowers and led to the Cold War, during which both countries struggled for ideological dominance and international influence. Following the Soviet Union's collapse and the end of the Cold War in 1991, the U.S. emerged as the world's sole superpower, wielding significant geopolitical influence globally. The U.S. national government is a presidential constitutional federal republic and liberal democracy with three separate branches: legislative, executive, and judicial. It has a bicameral national legislature composed of the House of Representatives, a lower house based on population, and the Senate, an upper house based on equal representation for each state. The country's Democratic and Republican parties have dominated American politics since the 1850s. Federalism provides substantial autonomy to the 50 states, while American values are based on a democratic political tradition that draws its inspiration from the European Enlightenment movement. One of the world's most developed countries, the United States accounted for over a quarter of nominal global economic output in 2024, and its economy has been the largest by nominal GDP since about 1890. It possesses by far the largest amount of wealth of any country and has the highest disposable household income per capita among OECD countries, though U.S. wealth inequality is higher than in most other developed countries. The U.S. ranks among the world's highest in economic competitiveness, productivity, innovation, human rights, and higher education. Its hard power and American cultural influence have a global reach. The U.S. is a founding member of the World Bank, the Organization of American States, NATO, the G7, and the United Nations,[m] as well as a permanent member of the UN Security Council.";
std::string responseText = R"([
        {
          x: 0.266879,
          y: 0.381792,
          yaw: -1.738537,
          description: "",
          location_name: "Start",
          voice_message: "You have reached Start",
        },
        {
          x: 0.013481,
          y: 0.001174,
          yaw: -0.121321,
          description: "",
          location_name: "Wind Tunnel",
          voice_message: "You have reached Wind Tunnel",
        },
        {
          x: 0.333609,
          y: 0.722148,
          yaw: -0.631456,
          description: "",
          location_name: "Amul",
          voice_message: "You have reached Amul",
        },
        {
          x: 0.000499,
          y: 0.503416,
          yaw: -173.074398,
          description: "",
          location_name: "Bicycle Stand",
          voice_message: "You have reached bicycle stand",
        },
        {
          x: 0.00108,
          y: 0.63652,
          yaw: -177.963844,
          description: "",
          location_name: "SIT",
          voice_message: "You have reached S I T",
        },
        {
          x: 0.300962,
          y: 0.77485,
          yaw: 84.227386,
          description: "",
          location_name: "Warehouse",
          voice_message: "You have reached Warehouse",
        },

      ])";
// The United States of America (USA), commonly known as the United States (U.S.) or America, is a country primarily located in North America. It is a federal union of 50 states and Washington, D.C., its federal capital district. The 48 contiguous states border Canada to the north and Mexico to the south, with the semi-exclavic state of Alaska in the northwest and the archipelagic state of Hawaii in the Pacific Ocean. The U.S. also asserts sovereignty over five major island territories and various uninhabited islands.[j] The country has the world's third-largest land area[d] and third-largest population, exceeding 340 million.[k] The country also possesses the world's second-largest exclusive economic zone. Its three largest metropolitan areas are New York, Los Angeles, and Chicago, and its three most populous states are California, Texas, and Florida.Paleo-Indians migrated to North America across the Bering land bridge more than 12,000 years ago, and formed various civilizations and societies. Spanish exploration and colonization led to the establishment in 1513 of Spanish Florida, the first European colony in what is now the continental United States. Early French colonization failed, and major settlements came much later. Subsequent British colonization led to the first settlement of the Thirteen Colonies in Virginia in 1607. The development of intensive agriculture in the rapidly expanding colonies soon led to the forced migration of enslaved Africans. Clashes with the British Crown over taxation and political representation sparked the American Revolution, with the Second Continental Congress formally declaring independence on July 4, 1776. Following its victory in the 1775–1783 Revolutionary War, the country continued to expand westward across North America, resulting in the dispossession of native inhabitants. As more states were admitted,[l] a North–South division over slavery led to the secession of the Confederate States of America, which fought the Union in the 1861–1865 American Civil War. With the victory and preservation of the United States, slavery was abolished nationally. By 1900, the country had established itself as a great power, a status solidified after its involvement in World War I. After Japan's attack on Pearl Harbor in December 1941, the U.S. entered World War II. Its aftermath left the U.S. and the Soviet Union as the world's two superpowers and led to the Cold War, during which both countries struggled for ideological dominance and international influence. Following the Soviet Union's collapse and the end of the Cold War in 1991, the U.S. emerged as the world's sole superpower, wielding significant geopolitical influence globally. The U.S. national government is a presidential constitutional federal republic and liberal democracy with three separate branches: legislative, executive, and judicial. It has a bicameral national legislature composed of the House of Representatives, a lower house based on population, and the Senate, an upper house based on equal representation for each state. The country's Democratic and Republican parties have dominated American politics since the 1850s. Federalism provides substantial autonomy to the 50 states, while American values are based on a democratic political tradition that draws its inspiration from the European Enlightenment movement. One of the world's most developed countries, the United States accounted for over a quarter of nominal global economic output in 2024, and its economy has been the largest by nominal GDP since about 1890. It possesses by far the largest amount of wealth of any country and has the highest disposable household income per capita among OECD countries, though U.S. wealth inequality is higher than in most other developed countries. The U.S. ranks among the world's highest in economic competitiveness, productivity, innovation, human rights, and higher education. Its hard power and American cultural influence have a global reach. The U.S. is a founding member of the World Bank, the Organization of American States, NATO, the G7, and the United Nations,[m] as well as a permanent member of the UN Security Council.

size_t sentBytes = 0;  
const int chunkSize = 509;  // Max BLE payload size (512 MTU - 3 byte ATT header)
bool isTransmitting = false; // Flag to indicate if data is being sent

// BLE Server Callback
class ServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) { Serial.println("✅ Device Connected"); }
  void onDisconnect(BLEServer* pServer) {
    Serial.println("❌ Device Disconnected"); 
    isTransmitting = false;
    delay(500);  // Short delay before restarting
    pServer->getAdvertising()->start();  // Restart advertising
    Serial.println("📡 Restarted Advertising");}
};

// Function to send the next chunk
void sendNextChunk() {
    while (sentBytes < responseText.length()) {
        std::string chunk = responseText.substr(sentBytes, chunkSize);
        sentBytes += chunk.length();
        
        responseCharacteristic->setValue(chunk);
        responseCharacteristic->notify();
        
        Serial.println("📤 Sent Chunk: " + String(chunk.c_str()));
        
        delay(30);  // Small delay to prevent BLE buffer overflow
    }

    // Send "END" signal when finished
    responseCharacteristic->setValue("END");
    responseCharacteristic->notify();
    Serial.println("✅ Sent END Signal.");

    isTransmitting = false; // Reset transmission flag
}

// Command Processing Callback
class CommandCallback : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *characteristic) {
    std::string request = characteristic->getValue();  
    Serial.println("📩 Received Command: " + String(request.c_str()));

    if (request == "GET_DATA" && !isTransmitting) {
        sentBytes = 0;  // Reset counter
        isTransmitting = true;
        Serial.println("🚀 Sending Large Response...");
        sendNextChunk();  // Automatically send all data
    }
  }
};

void setup() {

  // Initialize BLE
  BLEDevice::init("ESP32_BLE_API");
  BLEServer *server = BLEDevice::createServer();
  server->setCallbacks(new ServerCallbacks());

  // ✅ Set MTU to 512 (max possible for ESP32)
  esp_ble_gatt_set_local_mtu(512);  

  // Create BLE Service
  BLEService *service = server->createService(SERVICE_UUID);

  // Create Command Characteristic (write requests)
  BLECharacteristic *commandCharacteristic = service->createCharacteristic(
    COMMAND_CHAR_UUID,
    BLECharacteristic::PROPERTY_WRITE
  );
  commandCharacteristic->setCallbacks(new CommandCallback());

  // Create Response Characteristic (notify responses)
  responseCharacteristic = service->createCharacteristic(
    RESPONSE_CHAR_UUID,
    BLECharacteristic::PROPERTY_NOTIFY
  );
  responseCharacteristic->addDescriptor(new BLE2902());  // Enable notifications

  // Start Service and Advertising
  service->start();
  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  advertising->start();
  
  Serial.println("✅ ESP32 BLE API Ready");
}
// void loop(){}
// void loop() {
//   if (Serial.available() > 0) {
//     std::string responseText = Serial.readStringUntil('\n').c_str();  // Convert String to std::string
//     Serial.print("Received: ");
//     Serial.println(responseText.c_str());  // Print the received string
// }
// delay(100);
//   // No need to do anything in loop, BLE events handle everything
// }

void loop() {
}
