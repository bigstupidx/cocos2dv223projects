#ifndef __PLANE_LAYER_H__
#define __PLANE_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

#define PLANE_TAG 100

class PlaneLayer: public CCLayer {
public:
	PlaneLayer();
	~PlaneLayer();


	static PlaneLayer* create();

	virtual bool init();


	void moveTo(CCPoint location);
	void blowUp(int passScore);
	void removePlane();

public:
	static PlaneLayer* sharedPlane;
	bool is_alive;
	int score;
};

#endif //__PLANE_LAYER_H__
