
//1. without controller seperation (controller is game object, close to current stucture)
//game sim totally reproduced for the 2 versions

struct MobaControllerClient //(client)
{
	MobaModel m;
	MobaView v;

	MobaControllerClient::Update();

};

struct MobaControllerServer
{
	MobaModel m;
	MobaView v;//trivial

	MobaControllerServer::Update();

};



struct SMobaGameModel {};
struct SMobaSharedControl {};
struct SMobaClientView {};
struct SMobaClientControl {};
struct SMobaServerView {};
struct SMobaServerControl {};


//2.without reusable control.
	//(if we consider localised game flow logic part of model and use this structure, gotta make managers that contain common game flow)


struct SMobaGame
{
	SMobaGameModel m;
};

struct SMobaClientGame
{
	//SMobaClientGameState cm; Client only model? enviroment sim doesnt effect server?)
	SMobaGame g;
	SMobaClientView v;//is ui view/model here wrapped with game view (currently is). feels weird.//im my game view observes model directly
	SMobaClientControl cc;//would include directinput etc
};

struct SMobaServerGame
{
	SMobaGame g;
	SMobaServerView v;//trivial
	SMobaServerControl cc;
};

//3. might be risky (in struct reusable controller functionality)
//GameController would accept SMobaClientGame (or derivatives for game modes) as param

struct SMobaGame
{
	SMobaGameModel m;
	SMobaSharedControl sc; //perform actions on indivual actors //some simulation flow away from main loop (used client AND server)
							//this is oftnen described as the model
};

struct SMobaClientGame
{
	//SMobaClientGameState cm; Client only model? enviroment sim doesnt effect server?)
	SMobaGame g;
	SMobaClientView v(v_game, v_ui);//is ui view/model here wrapped with game view (currently is). feels weird.
	SMobaClientControl cc;//would include directinput etc
};

struct SMobaServerGame
{
	SMobaGame g;
	SMobaServerView v;
	SMobaServerControl cc;
};



//4. Reusable Control, UI and game mvc seperate (although would have to have shared control)
struct SMobaGame
{
	SMobaGameModel m_g;
	SMobaSharedControl sc;
};

struct SMobaGameUI
{
	SMobaGameUIModel m_ui;                              //SMobaSharedUIControl sc;
};

struct SMobaClientGame
{
	//SMobaClientGameState cm; Client only model? enviroment sim doesnt effect server?)
	SMobaGame g;
	SMobaGameUI g_ui;

	SMobaClientGameView v_g;//is ui view/model here wrapped with game view (currently is). feels weird.
	SMobaClientUIView v_ui;

	SMobaClientControl cc;//would include directinput etc
};

struct SMobaServerGame
{
	SMobaGame g;
	SMobaServerView v;//trivial
	SMobaServerControl cc;
};



//input / network event control initialised and operate outside of serverGame / client game
