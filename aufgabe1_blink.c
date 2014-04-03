#include <appTimer.h>
#include <zdo.h>
#include <blink.h>
#include <taskManager.h>


static HAL_AppTimer_t yellow_timer;
static HAL_AppTimer_t orange_timer;
static HAL_AppTimer_t red_timer;

static void yellow_timer_fired(void);
static void red_timer_fired(void);
static void orange_timer_fired(void);

void APL_TaskHandler(void) {
	
	//DDRE |= (1 << PE0) | (1 << PE1) | (1 << PE2);
	BSP_OpenLeds();
	yellow_timer.interval = 1000;
	yellow_timer.mode = TIMER_REPEAT_MODE;
	yellow_timer.callback = yellow_timer_fired;
	
	red_timer.interval = 500;
	red_timer.mode = TIMER_REPEAT_MODE;
	red_timer.callback = red_timer_fired;
	
	orange_timer.interval = 250;
	orange_timer.mode = TIMER_REPEAT_MODE;
	orange_timer.callback = orange_timer_fired;
	
	
	HAL_StartAppTimer(&yellow_timer);
	HAL_StartAppTimer(&orange_timer);
	HAL_StartAppTimer(&red_timer);
}

static void yellow_timer_fired() {
	//PORTE ^= (1 << PE0);
	BSP_ToggleLed(LED_YELLOW);
}

static void orange_timer_fired() {
	//PORTE ^= (1 << PE1);
	BSP_ToggleLed(LED_ORANGE);
}

static void red_timer_fired() {
	//PORTE ^= (1 << PE2);
	BSP_ToggleLed(LED_RED);
}


void ZDO_MgmtNwkUpdateNotf(ZDO_MgmtNwkUpdateNotf_t *nwkParams)
{
  nwkParams = nwkParams;  // Unused parameter warning prevention
}


void ZDO_WakeUpInd(void)
{
}

#ifdef _BINDING_

void ZDO_BindIndication(ZDO_BindInd_t *bindInd)
{
  (void)bindInd;
}


void ZDO_UnbindIndication(ZDO_UnbindInd_t *unbindInd)
{
  (void)unbindInd;
}
#endif //_BINDING_


int main(void)
{
  SYS_SysInit();

  for(;;)
  {
    SYS_RunTask();
  }
}
