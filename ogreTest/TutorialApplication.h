#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.h"

class TutorialApplication : public BaseApplication
{
public:
    TutorialApplication(void);
    virtual ~TutorialApplication(void);
	virtual void go() override;

protected:
    virtual void createScene() override;
};

#endif // #ifndef __TutorialApplication_h_

