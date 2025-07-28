//using binary semaphore for signaling the led for blinking
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

static const int led_pin=LED_BUILTIN;

static SemaphoreHandle_t bin_sem;
void blinkLED(void *parameters) {
  int num = *(int *)parameters;
  xSemaphoreGive(bin_sem);
  // Print the parameter
  Serial.print("Received: ");
  Serial.println(num);

  // Configure the LED pin
  pinMode(led_pin, OUTPUT);

  // Blink forever and ever
  while (1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(num / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(num / portTICK_PERIOD_MS);
  }
}

void setup() {
  long int delay_arg;
  Serial.begin(115200);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("---FreeRTOS Mutex Challenge---");
  Serial.println("Enter a number for delay (milliseconds)");

  // Wait for input from Serial
  while (Serial.available() <= 0);

  // Read integer value
  delay_arg = Serial.parseInt();
  Serial.print("Sending: ");
  Serial.println(delay_arg);

  bin_sem = xSemaphoreCreateBinary();

  // Start task 1
  xTaskCreatePinnedToCore(blinkLED,
                          "Blink LED",
                          1024,
                          (void *)&delay_arg,
                          1,
                          NULL,
                          app_cpu);
  xSemaphoreTake(bin_sem,portMAX_DELAY);
  // Show that we accomplished our task of passing the stack-based argument
  Serial.println("Done!");
}
void loop() {
  // put your main code here, to run repeatedly:

}
