#pragma once

class Camera : public SingletonBase<Camera>
{
public:
	friend SingletonBase<Camera>;

	void Update();
	void Render();

	void Move();
	void UpdateView();

	const Vector3 GetPosition() { return position; }

	void SetPosition(Vector3 position) { this->position = position; }

	void UnProjection(Vector3* out, Vector3 source, Matrix world = Values::Identity); // 2D->3D

private:
	Camera();
	~Camera();

private:
	VPBuffer* vpb = nullptr;
	Matrix view, proj;

	Vector3 position = Values::ZeroVec3;
	float cameraSpeed = 100.0f;
};