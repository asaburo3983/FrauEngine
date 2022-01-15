#pragma once
#include "Application.h"

#include "Objects.h"

#include "Loading.h"
#include "Fade.h"

#include "Player.h"
#include "Stage.h"
#include "MaterialLinkerData.h"
#include "NovelSystem.h"
#include "CameraWork.h"
#include "EventManager.h"
#include "TutorialSystem.h"
#include "NormalUI.h"
#include "PlanterSystem.h"
#include "NextDay.h"

using namespace frauEngine;

void CommonDataLoad();

void CommonUpdate();

void CommonDraw();

void CommonDrawNonePostEffect();