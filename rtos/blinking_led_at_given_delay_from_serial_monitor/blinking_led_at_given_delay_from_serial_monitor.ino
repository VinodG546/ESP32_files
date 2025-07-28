#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

static const uint8_t buf_len = 20;
static const int led_pin = LED_BUILTIN;
static int led_delay = 500;   // milliseconds

void toggleled(void *parameter) {
  while (1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(led_delay / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(led_delay / portTICK_PERIOD_MS);
  }
}

void readserial(void *parameter) {
  char c;
  char buf[buf_len];
  int idx = 0;
  memset(buf, 0, buf_len);

  while (1) {
    if (Serial.available() > 0) {
      c = Serial.read();

      if (c == '\n') {
        led_delay = atoi(buf);
        Serial.print("Updated LED delay to: ");
        Serial.println(led_delay);
        memset(buf, 0, buf_len);
        idx = 0;
      } else if (idx < buf_len - 1 && isDigit(c)) {
        buf[idx++] = c;
      }
    }
    vTaskDelay(10 / portTICK_PERIOD_MS); // avoid hogging CPU
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  delay(1000);

  Serial.println("Multi-task LED demo");
  Serial.println("Enter delay in ms (e.g., 1000) followed by Enter");

  xTaskCreatePinnedToCore(
    toggleled,
    "Toggle LED",
    1024,
    NULL,
    1,
    NULL,
    app_cpu
  );

  xTaskCreatePinnedToCore(
    readserial,
    "Read Serial",
    2048,  // increased stack size for Serial operations
    NULL,
    1,
    NULL,
    app_cpu
  );

  vTaskDelete(NULL); // delete setup() task
}

void loop() {
  // Do nothing here
}
