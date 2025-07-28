//using queues instead of global variables for avoiding the consequences of data corruption 
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

static const int msg_queue_len = 5;

static QueueHandle_t msg_queue;
// tasks

void printmsg(void *parameter){
  int item;
  while(1){
    if(xQueueReceive(msg_queue,(void*)&item,0)==pdTRUE){
     
    }
     Serial.println(item);
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  vTaskDelay(1000/portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("freertos queue");
  msg_queue = xQueueCreate(msg_queue_len,sizeof(int));
  xTaskCreatePinnedToCore(
    printmsg,
    "print Message",
    1024,  // increased stack size for Serial operations
    NULL,
    1,
    NULL,
    app_cpu
  );
}

void loop() {
  static int num=0;
  // put your main code here, to run repeatedly:
  if(xQueueSend(msg_queue,(void*)&num,10)!=pdTRUE){
    Serial.println("queue full");
  }
  num++;
  vTaskDelay(500/portTICK_PERIOD_MS);
}
