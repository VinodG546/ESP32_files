
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

// Constants
static const int ledPin = LED_BUILTIN;
static const int max_permit = 2;  // max tasks allowed to enter critical section

// Semaphore
SemaphoreHandle_t cnt_sem;

// LED blink task
void blinkTask(void *parameter) {
  int delayTime = *(int *)parameter;
  free(parameter);  // free heap after use

  while (1) {
    // Try to take the semaphore
    if (xSemaphoreTake(cnt_sem, portMAX_DELAY) == pdTRUE) {
      Serial.print("Task with delay ");
      Serial.print(delayTime);
      Serial.println(" ms is running...");

      digitalWrite(ledPin, HIGH);
      vTaskDelay(delayTime / portTICK_PERIOD_MS);
      digitalWrite(ledPin, LOW);
      vTaskDelay(delayTime / portTICK_PERIOD_MS);

      // Release the semaphore
      xSemaphoreGive(cnt_sem);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println("\n--- FreeRTOS Counting Semaphore Test ---");

  // Create counting semaphore with max and initial count
  cnt_sem = xSemaphoreCreateCounting(max_permit, max_permit);
  if (cnt_sem == NULL) {
    Serial.println("Failed to create semaphore!");
    while (1);
  }

  // Create 3 tasks with different delays
  int *d1 = (int *)malloc(sizeof(int));
  int *d2 = (int *)malloc(sizeof(int));
  int *d3 = (int *)malloc(sizeof(int));
  *d1 = 100;
  *d2 = 300;
  *d3 = 600;

  xTaskCreatePinnedToCore(blinkTask, "Blink100", 2048, d1, 1, NULL, app_cpu);
  xTaskCreatePinnedToCore(blinkTask, "Blink300", 2048, d2, 1, NULL, app_cpu);
  xTaskCreatePinnedToCore(blinkTask, "Blink600", 2048, d3, 1, NULL, app_cpu);
}

void loop() {
  // Main loop does nothing
}
