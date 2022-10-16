
#include "ShipCameraShake.h"

UShipCameraShake::UShipCameraShake()
{
	OscillationDuration = 0.1f;//��������� ������ ����� ��������
	//����� ���������� �������
	OscillationBlendInTime = 0.05f;
	OscillationBlendOutTime = 0.25f;

	//������ ��������� ���������� X Y ��� ������
	RotOscillation.Pitch.Amplitude = FMath::RandRange(15.0f, 20.0f);
	RotOscillation.Pitch.Frequency = FMath::RandRange(25.0f, 25.0f);

	RotOscillation.Yaw.Amplitude = FMath::RandRange(15.0f, 20.0f);
	RotOscillation.Yaw.Frequency = FMath::RandRange(25.0f, 25.0f);
}