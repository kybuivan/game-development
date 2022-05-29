#ifndef __LAYER_H__
#define __LAYER_H__
class Layer
{
public:
	
	virtual void render() = 0;
	virtual void update() = 0;
	
protected:

	virtual ~Layer() {}
	
};
#endif//__LAYER_H__