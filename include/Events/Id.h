#ifndef EVENT_ID_H
#define EVENT_ID_H

enum EventId
{
    CHANGE_STATE,
    PUSH_STATE,
    POP_STATE,
    PLAY_SOUND,
    SOUND_VOLUME_CHANGED,
    MUSIC_VOLUME_CHANGED,
    PLAY_MUSIC,
    BALL_COLLISION,
    GOAL_COLLISION,
    LEFT_GOAL_COLLISION,
    RIGHT_GOAL_COLLISION,
	PADDLE_COLLISION
};

enum ObjectId
{
    BALL,
    LEFT_GOAL,
    RIGHT_GOAL,
    LEFT_PADDLE,
    RIGHT_PADDLE,
    WALL,
    NONE
};

#endif // ID_H
