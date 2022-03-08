#ifndef __STAGE_H__
#define __STAGE_H__

#include "../utils/defs.h"

class Stage
{
public:
    Stage() {}

    ~Stage();

public:
    void initStage(void);

    void renderer(void);
};

#endif