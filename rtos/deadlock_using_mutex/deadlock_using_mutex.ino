//to avoid deadlock to happen give delays between two tasks in the mean time the the task cant acceess
//the mutex2 than it has to release
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

SemaphoreHandle_t mutex1;
SemaphoreHandle_t mutex2;

void blinkled1(void *parameter) {
  while (1) {
    Serial.println("Task A trying to take mutex1");
    xSemaphoreTake(mutex1, portMAX_DELAY);
    Serial.println("Task A took mutex1");

    vTaskDelay(100 / portTICK_PERIOD_MS);  // Intentional delay

    Serial.println("Task A trying to take mutex2");
    xSemaphoreTake(mutex2, portMAX_DELAY);
    Serial.println("Task A took mutex2");

    Serial.println("Task A doing work");
    vTaskDelay(500 / portTICK_PERIOD_MS);

    xSemaphoreGive(mutex2);
    xSemaphoreGive(mutex1);

    Serial.println("Task A done, going to sleep");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void blinkled2(void *parameter) {
  while (1) {
    Serial.println("Task B trying to take mutex2");
    xSemaphoreTake(mutex2, portMAX_DELAY);
    Serial.println("Task B took mutex2");

    vTaskDelay(100 / portTICK_PERIOD_MS);  // Intentional delay

    Serial.println("Task B trying to take mutex1");
    xSemaphoreTake(mutex1, portMAX_DELAY);
    Serial.println("Task B took mutex1");

    Serial.println("Task B doing work");
    vTaskDelay(500 / portTICK_PERIOD_MS);

    xSemaphoreGive(mutex1);
    xSemaphoreGive(mutex2);

    Serial.println("Task B done, going to sleep");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("-- FreeRTOS Deadlock Demo (Forced) --");

  mutex1 = xSemaphoreCreateMutex();
  mutex2 = xSemaphoreCreateMutex();

  // Same priority for both tasks
  xTaskCreatePinnedToCore(blinkled1, "TaskA", 2048, NULL, 1, NULL, app_cpu);
  xTaskCreatePinnedToCore(blinkled2, "TaskB", 2048, NULL, 1, NULL, app_cpu);
}

void loop() {
  // Optional: Monitor system freeze
  static uint32_t t = 0;
  if (millis() - t > 2000) {
    Serial.println("System heartbeat: loop() alive");
    t = millis();
  }
}
