#include "PathController.h"


Pathfinder * PathController::sm_pathfinder = NULL;


PathController::PathController()
{

}

PathController::PathController(Pathfinder * pathfinder, WalkState * walkState, Actor *  owner)
{
	if (sm_pathfinder == NULL) sm_pathfinder = pathfinder;

	m_walkState = walkState;
	m_owner = owner;

	m_isEnabled = true;

	m_state = pathStateStandby;

	m_endpoint = LMVector3(0.0f, 0.0f, 0.0f);
}

PathController::~PathController()
{

}

void PathController::Update(float deltaTime)
{
	if (!m_isEnabled) return;

	switch (m_state) {
		case pathStateStandby:Standby(deltaTime); break;
		case pathStateRequestPath:RequestPath(deltaTime); break;
		case pathStateNavigate:Navigate(deltaTime); break;
		case pathStateAlternativePath:AlternativePath(deltaTime); break;
		default: break;
	}
}

void PathController::Render()
{

}

//private State Control functions ///////////////////////////
void PathController::OnEnterStandby()
{
	m_state = pathStateStandby;
}

void PathController::Standby(float deltaTime)
{
	m_walkState->Update(deltaTime);
}

void PathController::OnExitStandby()
{

}

void PathController::OnEnterRequestPath()
{
	m_state = pathStateRequestPath;
}

void PathController::RequestPath(float deltaTime)
{
	m_walkState->Update(deltaTime);
}

void PathController::OnExitRequestPath()
{

}

void PathController::OnEnterNavigate()
{
	m_state = pathStateNavigate;

	m_nextNodeIndex = 0;
	m_nextNode = m_currentPath.at(m_nextNodeIndex);

	m_walkState->ExitCurrentState();
	m_walkState->OnEnterWalking(m_nextNode);
}

void PathController::Navigate(float deltaTime)
{
	if ((m_owner->GetPhysicsObject()->GetPosition())->DisplacementMag(*m_nextNode) < 0.05f)
	{
		m_nextNodeIndex++;

		if (m_nextNodeIndex < m_currentPath.size())
		{
			m_nextNode = m_currentPath.at(m_nextNodeIndex);

			m_walkState->ExitCurrentState();
			m_walkState->OnEnterWalking(m_nextNode);
		}
		else
		{
			if (m_walkState->GetState() != walkStateWalking)
			{
				OnExitNavigate();
				OnEnterStandby();
			}
		}
	}

	m_walkState->Update(deltaTime);
}

void PathController::OnExitNavigate()
{
	m_walkState->ExitCurrentState();
	m_walkState->OnEnterStopped();
}

void PathController::OnEnterAlternativePath()
{
	m_state = pathStateAlternativePath;
}

void PathController::AlternativePath(float deltaTime)
{
	m_walkState->Update(deltaTime);
}

void PathController::OnExitAlternativePath()
{

}

void PathController::ExitCurrentState()
{
	switch (m_state) {
		case pathStateStandby:OnExitStandby(); break;
		case pathStateRequestPath:OnExitRequestPath(); break;
		case pathStateNavigate:OnExitNavigate(); break;
		case pathStateAlternativePath:OnExitAlternativePath(); break;
		default: break;
	}
}

//public external control //

void PathController::SetToStandby()
{
	if (m_state != pathStateStandby)
	{
		ExitCurrentState();
		OnEnterStandby();
	}
}

bool PathController::WalkToPosition(bool ignoreRateLowering, LMVector3 * target, LMVector3 * origin)
{
	m_endpoint = *target;

	if (m_isEnabled)//PathFinding Enabled
	{
		ExitCurrentState();

		//todo okay we might need delta/gametime param to set up a timer or some other way of not searching every update
		//but rand atm

		if (rand() > 0.90f || ignoreRateLowering)
		{
			sm_pathfinder->GeneratePath(
				&m_currentPath,
				origin,
				&m_endpoint );
			
			m_currentPath.push_back(&m_endpoint);
		}


		OnEnterNavigate();

	}
	else//PathFinding Disabled (go there)
	{
		m_walkState->ExitCurrentState();
		m_walkState->OnEnterWalking(&m_endpoint);//todo no new keyword
		//TODO change WalkToPosition target parameter to a const LMVector3
		return false;
	}

	return true;
}

//void GeneratePath(vector<PathNode *> * pathOut, LMVector3 * position, LMVector3 * target);

PathState PathController::GetState()
{
	return m_state;
}


bool PathController::GetIsEnabled()
{
	return m_isEnabled;
}

void PathController::SetEnabled(bool newEnabledState)
{
	m_isEnabled = newEnabledState;
}