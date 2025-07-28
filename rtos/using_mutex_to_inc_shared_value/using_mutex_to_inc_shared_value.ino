#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

static int shared_var=0;
static SemaphoreHandle_t mutex;

//tasks
void inctask(void *parameter){
  int local_var;
  while(1){
    if(xSemaphoreTake(mutex,0)==pdTRUE){
      local_var=shared_var;
      local_var++;
      vTaskDelay(random(100,500)/portTICK_PERIOD_MS);
      shared_var=local_var;
      xSemaphoreGive(mutex);
      Serial.println(shared_var);
   }
    else{

    }
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  vTaskDelay(500/portTICK_PERIOD_MS);
  Serial.println("--freertos race condition demo--");
  mutex=xSemaphoreCreateMutex();
  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
            inctask,      // Function to be called
            "incrementing shared var 1",   // Name of task
            1024,           // Stack size (bytes in ESP32, words in FreeRTOS)
            NULL,           // Parameter to pass
            1,              // Task priority
            NULL,           // Task handle
            app_cpu);       // Run on one core for demo purposes (ESP32 only)
  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
            inctask,      // Function to be called
            "incrementing shared var 2",   // Name of task
            1024,           // Stack size (bytes in ESP32, words in FreeRTOS)
            NULL,           // Parameter to pass
            1,              // Task priority
            NULL,           // Task handle
            app_cpu);       // Run on one core for demo purposes (ESP32 only)
  vTaskDelete(NULL);    
}

void loop() {
  // put your main code here, to run repeatedly:

}
