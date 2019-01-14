#include "CGlobalDate.h"

CGlobalDate* CGlobalDate::instance = 0;

CGlobalDate::CGlobalDate():collectionenableonece(0),mvconfigenable(0)
{

}
CGlobalDate* CGlobalDate::Instance()
{
    if(instance == 0)
        instance =  new CGlobalDate();
    return instance;
}

