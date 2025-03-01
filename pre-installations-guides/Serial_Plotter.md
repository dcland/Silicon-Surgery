# **Arduino IDE: Serial Plotter 📊**

The **Serial Plotter** is a tool that visualizes real-time data from your Arduino.

## **🔹 How to Use the Serial Plotter**
1. Open **Arduino IDE** and load your sketch.
2. In `setup()`, initialize the serial port:
   ```cpp
   void setup() {
       Serial.begin(9600);
   }
   ```
3. In `loop()`, send values to the plotter:
   ```cpp
   void loop() {
       int sensorValue = analogRead(A0);
       Serial.println(sensorValue);
       delay(100);
   }
   ```
4. **Open the Serial Plotter** from **Tools > Serial Plotter**.
5. Observe the real-time graph.

✅ This is useful for visualizing sensor data and debugging values.
