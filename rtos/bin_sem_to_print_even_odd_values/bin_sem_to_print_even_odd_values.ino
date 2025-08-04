static const BaseType_t app_cpu = 0;
static const BaseType_t pro_cpu = 1;

static SemaphoreHandle_t bin_sem;
int num = 0;

void eventask(void *parameter) {
  while (1) {
    xSemaphoreTake(bin_sem, portMAX_DELAY);
    if (num % 2 == 0) {
      Serial.print("even ");
      Serial.println(num);
      num += 1;
      vTaskDelay(500 / portTICK_PERIOD_MS);  // delay only if executed
    }
    xSemaphoreGive(bin_sem);
    vTaskDelay(10 / portTICK_PERIOD_MS);  // prevent tight loop
  }
}

void oddtask(void *parameter) {
  while (1) {
    xSemaphoreTake(bin_sem, portMAX_DELAY);
    if (num % 2 != 0) {
      Serial.print("odd ");
      Serial.println(num);
      num += 1;
      vTaskDelay(500 / portTICK_PERIOD_MS);  // delay only if executed
    }
    xSemaphoreGive(bin_sem);
    vTaskDelay(10 / portTICK_PERIOD_MS);  // prevent tight loop
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("FreeRTOS binary semaphore");
  Serial.println();

  bin_sem = xSemaphoreCreateBinary();
  xSemaphoreGive(bin_sem);  // make semaphore available at start

  xTaskCreatePinnedToCore(eventask, "even numbers", 2048, NULL, 1, NULL, app_cpu);
  xTaskCreatePinnedToCore(oddtask, "odd numbers", 2048, NULL, 1, NULL, pro_cpu);
}

void loop() {
  // Do nothing
}
