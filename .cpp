#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Ganti dengan kredensial WiFi Anda
char ssid[] = "Zaky";     // Nama WiFi Anda
char pass[] = "70240900"; // Password WiFi Anda

// Ganti dengan Blynk Auth Token Anda
char auth[] = "2aroxWWyv1HW9nqksUOzkZIJh9wuiw0L"; 

// Pin untuk sensor gas
const int gasSensorPin = A0; // Ganti dengan pin yang sesuai

void setup() {
    Serial.begin(115200);
    Blynk.begin(auth, ssid, password);
}

void loop() {
    Blynk.run();

    // Membaca nilai dari sensor gas
    int gasValue = analogRead(gasSensorPin);
    int gasPercentage = map(gasValue, 0, 1023, 0, 100); // Sesuaikan dengan karakteristik sensor Anda

    // Mengirim data ke Blynk
    Blynk.virtualWrite(V0, gasPercentage); // Kirim persentase gas ke V0
    Blynk.virtualWrite(V1, determineGasStatus(gasPercentage)); // Kirim status gas ke V1

    delay(30000); // Kirim data setiap 30 detik
}

// Fungsi untuk menentukan status gas
String determineGasStatus(int percentage) {
    if (percentage <= 20) {
        return "AMAN";
    } else if (percentage <= 40) {
        return "WASPADA";
    } else {
        return "BAHAYA";
    }
}
