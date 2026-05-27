#include "/home/codeleaded/System/Static/Library/Math.h"
#include "/home/codeleaded/System/Static/Library/Random.h"
#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"

float fDistance = 0.0f;
float fCurvature = 0.0f;
float fTrackCurvature = 0.0f;
float fTrackDistance = 0.0f;
float fCarPos = 0.0f;
float fPlayerCurvature = 0.0f;
float fSpeed = 0.0f;
Vector vecTrack;

void Setup(AlxWindow* w){
    vecTrack = Vector_New(sizeof(Vec2));

    Vector_Push(&vecTrack,(Vec2[]){{ 0.0f,  10.0f }});
	Vector_Push(&vecTrack,(Vec2[]){{ 0.0f, 200.0f }});
	Vector_Push(&vecTrack,(Vec2[]){{ 1.0f, 200.0f }});
	Vector_Push(&vecTrack,(Vec2[]){{ 0.0f, 400.0f }});
	Vector_Push(&vecTrack,(Vec2[]){{-1.0f, 100.0f }});
	Vector_Push(&vecTrack,(Vec2[]){{ 0.0f, 200.0f }});
	Vector_Push(&vecTrack,(Vec2[]){{-1.0f, 200.0f }});
	Vector_Push(&vecTrack,(Vec2[]){{ 1.0f, 200.0f }});
	Vector_Push(&vecTrack,(Vec2[]){{ 0.0f, 200.0f }});
	Vector_Push(&vecTrack,(Vec2[]){{ 0.2f, 500.0f }});
	Vector_Push(&vecTrack,(Vec2[]){{ 0.0f, 200.0f }});

	for(int i = 0;i<vecTrack.size;i++){
        Vec2 p = *(Vec2*)Vector_Get(&vecTrack,i);
        fTrackDistance += p.y;
    }	
}
void Update(AlxWindow* w){
    if(Stroke(ALX_KEY_W).DOWN)
        fSpeed += 2.0f * w->ElapsedTime;
	else
		fSpeed -= 1.0f * w->ElapsedTime;
       
    
    int nCarDirection = 0;
    if(Stroke(ALX_KEY_A).DOWN){
        fPlayerCurvature -= 0.7f * w->ElapsedTime * (1.0f - fSpeed / 2.0f);
		nCarDirection = -1;
    }
    if(Stroke(ALX_KEY_D).DOWN){
        fPlayerCurvature += 0.7f * w->ElapsedTime * (1.0f - fSpeed / 2.0f);
		nCarDirection = +1;
    }
    
    Clear(BLACK);


	if (fabs(fPlayerCurvature - fTrackCurvature) >= 0.8f)
		fSpeed -= 5.0f * w->ElapsedTime;

	if (fSpeed < 0.0f)	fSpeed = 0.0f;
	if (fSpeed > 1.0f)	fSpeed = 1.0f;
		
	fDistance += (70.0f * fSpeed) * w->ElapsedTime;
		
	float fOffset = 0;
	int nTrackSection = 0;

	//fCurrentLapTime += w->ElapsedTime;
	//if (fDistance >= fTrackDistance)
	//{
	//	fDistance -= fTrackDistance;
	//	listLapTimes.push_front(fCurrentLapTime);
	//	listLapTimes.pop_back();
	//	fCurrentLapTime = 0.0f;
	//}
	
	while (nTrackSection < vecTrack.size && fOffset <= fDistance){
        Vec2 p = *(Vec2*)Vector_Get(&vecTrack,nTrackSection);
		fOffset += p.y;
		nTrackSection++;
	}
	
    Vec2 p = *(Vec2*)Vector_Get(&vecTrack,nTrackSection - 1);
	float fTargetCurvature = p.x;
	float fTrackCurveDiff = (fTargetCurvature - fCurvature) * w->ElapsedTime * fSpeed;
	fCurvature += fTrackCurveDiff;
	fTrackCurvature += (fCurvature) * w->ElapsedTime * fSpeed;
	

    Rect_RenderXX(WINDOW_STD_ARGS,0,0,GetWidth(),GetHeight() / 4,LIGHT_BLUE);
    Rect_RenderXX(WINDOW_STD_ARGS,0,GetHeight() / 4,GetWidth(),GetHeight() / 2,BLUE);

	for (int x = 0; x < GetWidth(); x++){
		int nHillHeight = (int)(fabs(sinf((float)x / ((float)GetWidth()) + fTrackCurvature) * (GetHeight() * 0.2f)));
		
        for (int y = (GetHeight() / 2) - nHillHeight; y < GetHeight() / 2; y++)
			Point_RenderX(WINDOW_STD_ARGS,x,y,DARK_YELLOW);
	}

	for (int y = 0; y < GetHeight() / 2; y++)
		for (int x = 0; x < GetWidth(); x++){
			float fPerspective = (float)y / (GetHeight()/2.0f);
			float fRoadWidth = 0.1f + fPerspective * 0.8f; // Min 10% Max 90%
			float fClipWidth = fRoadWidth * 0.15f;
			fRoadWidth *= 0.5f;	// Halve it as track is symmetrical around center of track, but offset...
			
            float fMiddlePoint = 0.5f + fCurvature * powf((1.0f - fPerspective), 3);
			
            int nLeftGrass = (fMiddlePoint - fRoadWidth - fClipWidth) * GetWidth();
			int nLeftClip = (fMiddlePoint - fRoadWidth) * GetWidth();
			int nRightClip = (fMiddlePoint + fRoadWidth) * GetWidth();
			int nRightGrass = (fMiddlePoint + fRoadWidth + fClipWidth) * GetWidth();
			
			int nRow = GetHeight() / 2 + y;
			int nGrassColour = sinf(20.0f *  powf(1.0f - fPerspective,3) + fDistance * 0.1f) > 0.0f ? GREEN : DARK_GREEN;
			int nClipColour = sinf(80.0f *  powf(1.0f - fPerspective, 2) + fDistance) > 0.0f ? RED : WHITE;
			
			int nRoadColour = (nTrackSection-1) == 0 ? WHITE : GRAY;
			
            if (x >= 0 && x < nLeftGrass)
				Point_RenderX(WINDOW_STD_ARGS,x,nRow,nGrassColour);
			if (x >= nLeftGrass && x < nLeftClip)
				Point_RenderX(WINDOW_STD_ARGS,x,nRow,nClipColour);
			if (x >= nLeftClip && x < nRightClip)
				Point_RenderX(WINDOW_STD_ARGS,x,nRow,nRoadColour);
			if (x >= nRightClip && x < nRightGrass)
				Point_RenderX(WINDOW_STD_ARGS,x,nRow,nClipColour);
			if (x >= nRightGrass && x < GetWidth())
				Point_RenderX(WINDOW_STD_ARGS,x,nRow,nGrassColour);
		}

    fCarPos = fPlayerCurvature - fTrackCurvature;
	float nCarPos = GetWidth() / 2 + ((int)(GetWidth() * fCarPos) / 2.0f) - 7;
    Rect_RenderXX(WINDOW_STD_ARGS,nCarPos,(float)GetHeight() * 0.8f,(float)GetWidth() * 0.05f,(float)GetHeight() * 0.05f,BLACK);
}
void Delete(AlxWindow* w){
    Vector_Free(&vecTrack);
}

int main(int argc,const char *argv[]){
    // 1900,1100,1,1
    if(Create("Arcade Racing Game",200,160,8,8,Setup,Update,Delete)){
        Start();
    }
    return 0;
}