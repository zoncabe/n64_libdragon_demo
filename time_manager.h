#ifndef TIME_H
#define TIME_H


typedef struct{

	float cur_frame;
	float last_frame;
	float frame_duration;
	float FPS;

}time_data_t;

float get_time(){

    float time_in_seconds = TIMER_MICROS(timer_ticks()) / 1000000.f;
    return time_in_seconds;
}

float cycles_to_sec(float cycles){

    float time = cycles / 1000000.f;
    return time;
}

void time_management(time_data_t *time_data){

    time_data->cur_frame = TIMER_MICROS(timer_ticks());

    time_data->frame_duration = cycles_to_sec(time_data->cur_frame - time_data->last_frame);

    time_data->FPS = 1 / time_data->frame_duration;

    time_data->last_frame = time_data->cur_frame;

}

#endif
