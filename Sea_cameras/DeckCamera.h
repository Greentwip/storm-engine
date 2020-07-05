// ==================================================================== ||
// Ship tie camera                                                      ||
// ==================================================================== ||
#ifndef _DECK_CAMERA_H_
#define _DECK_CAMERA_H_

#include "..\common_h\vmodule_api.h"
#include "..\common_h\dx8render.h"
#include "..\common_h\model.h"
#include "common_camera.h"

#define D3DFVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define AIM_SIZE	0.05f

class DECK_CAMERA : public COMMON_CAMERA
{
	struct VERTEX
	{
		D3DXVECTOR3 v;
		D3DCOLOR color;
		float tu;
		float tv;
	};

	VERTEX tri[4];

    // ��������� ����������� �� INI-����� //
    //--------------------------------------
	float	fSensivityDistance, fSensivityHeightAngle, fSensivityAzimuthAngle;
	float	fRockingX, fRockingZ;

	float MEN_STEP_UP;
	float MEN_STEP_MIN;
	float HEIGHT_MAX;
	float HEIGHT_MIN;
	float HEIGHT_STEP;
	float CAMERA_MAX_X, CAMERA_MIN_X;
	float DEFAULT_HEIGHT;
    //--------------------------------------

    CVECTOR g_gv0, g_gv1, g_gv2;

	MODEL * pModel; 
	VDX8RENDER * RenderService;
	CVECTOR camera_pos, camera_ang;
    float h_eye;
	RECT Screen_Rect;
	long lock_x;
	long lock_y;
	long vb_id;
	bool bLoad;
    NODE * pathNode;
    void SetStartPos();
    bool GetCrossXZ(CVECTOR &spos,CVECTOR &dv, CVECTOR &p1,CVECTOR &p2, CVECTOR &res);
	bool FindPath();
	void SetViewPoint(CVECTOR & cViewPoint);
	float MultiTrace(const CVECTOR & cvBase, const CVECTOR & cvDown, float fHBase);

public:
	DECK_CAMERA();
	~DECK_CAMERA();

	void SetCharacter(ATTRIBUTES *_pACharacter);

	void SetDevice();
	bool Init();
	void Move(DWORD DeltaTime);
	void Realize(dword Delta_Time);
	void Execute(dword Delta_Time);
	bool CreateState(ENTITY_STATE_GEN * state_gen);
	bool LoadState(ENTITY_STATE * state);
	dword AttributeChanged(ATTRIBUTES * pAttr);
	dword _cdecl ProcessMessage(MESSAGE & message);

	void Save(CSaveLoad * pSL);
	void Load(CSaveLoad * pSL);
};

#endif