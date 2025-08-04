//in this program i have used the api's for internal timers to make exact delay
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif
 
static TimerHandle_t one_shot=NULL;
static TimerHandle_t auto_shot=NULL;

void myTimerCallback(TimerHandle_t xTimer){
  Serial.println("Timer expired");
}

void setup(){
  Serial.begin(115200);
  vTaskDelay(1000/portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("--Free RTOS timer demo--");
  one_shot=xTimerCreate("one_shot_timer",2000/portTICK_PERIOD_MS,pdFALSE,(void*)0,myTimerCallback);
  auto_shot=xTimerCreate("auto_shot_timer",2000/portTICK_PERIOD_MS,pdTRUE,(void*)1,myTimerCallback);
  if(one_shot==NULL||auto_shot==NULL){
    Serial.println("could not create one of the timers");
  }
  else{
    vTaskDelay(1000/portTICK_PERIOD_MS);
    Serial.println("starting timers");
    xTimerStart(one_shot,portMAX_DELAY);
    xTimerStart(auto_shot,portMAX_DELAY);
  }
  vTaskDelete(NULL);
}
void loop(){

}