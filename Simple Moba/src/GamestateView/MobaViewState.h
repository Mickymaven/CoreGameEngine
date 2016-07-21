#if !defined(MOBAVIEWSTATE_H)
#define MOBAVIEWSTATE_H

#include <functional>
using namespace std::placeholders;

#include "../../../CoreGame/src/GameConfiguration.h"
#include "../../../CoreGame/src/Gamestate/AssetMeshNameEnum.h"
#include "../../../CoreGame/src/Gamestate/StandardMatch5v5State.h"
#include "../../../CoreGame/src/GamestateIO/DialogBehaviorIO.h"

#include "../../../EngineGameModuleDirectX9/src/Base/SpriteView.h"
#include "../../../EngineGameModuleDirectX9/src/Input/InputModel.h"

#include "../EnvironmentView/BoidstormView.h"
#include "../GameplayView/NPCView.h"
#include "../GameplayView/PlayerCharacterView.h"
#include "../GameplayView/VitalEntityView.h"
#include "../GamestateView/ThemeResources.h"
#include "../GamestateView/MobaGameElementsEnum.h"
#include "../GameplayView/Quests/QuestView.h"
#include "../GamestateViewIO/GameAssetFactory.h"
#include "../GameplayViewIO/PlayerCharacterViewFactory.h"
#include "../GameplayViewIO/NPCViewFactory.h"
#include "../GameplayViewIO/CharacterViewFactory.h"
#include "../GameplayViewIO/ActorViewFactory.h"
#include "../GameplayViewIO/AbilityViewFactory.h"
#include "../GameplayViewIO/BuffViewFactory.h"
#include "../GameplayViewIO/ItemViewFactory.h"
#include "../GameplayViewIO/GameMapViewFactory.h"
#include "../Input/Model/CameraInputModel.h"
#include "../Input/Model/CharacterInputModel.h"
#include "../Input/Model/ChatTextAreaInputModel.h"
#include "../Input/Model/DevInputModel.h"
#include "../Input/Model/EditorInputModel.h"
#include "../Input/Model/InterfaceInputModel.h"
#include "../Input/Model/KeyDialogInputModel.h"
#include "../Input/Model/MainMenuInputModel.h"
#include "../Input/Model/ShopMenuInputModel.h"
#include "../InputIO/KeybindData.h"
#include "../UI/GameCursor.h"
#include "../UI/GameMainMenu.h"
#include "../UI/GameMessage.h"
#include "../UI/GameShopMenu.h"
#include "../UI/HealthBar.h"
#include "../UI/StatPanel.h"
#include "../UI/Tooltips/TooltipController.h"
#include "../UI/UIMobaHud.h"



#include "../UI_Base/UIKeyDialog.h"
#include "../UI_Control/DialogScreenController.h"
#include "../UI_Control/IndicatorController.h"
#include "../UI_Control/InfoPanelController.h"

#include "BasicGameViewState.h"

enum Language
{
	languageEN,
	languageCount
};

enum MobaViewInitPhase
{
	mobaViewInitPhaseTheme,
	mobaViewInitPhaseInput,
	mobaViewInitPhaseActors,
	mobaViewInitPhaseQuests,
	mobaViewInitPhaseAssets,
	mobaViewInitPhaseInputGUI,
	mobaViewInitPhaseIndicators,
	mobaViewInitPhaseLighting,
	mobaViewInitPhaseCameras,
	mobaViewInitPhaseCount
};

enum VitalEntityVectorName
{
	vitalEntityVectorNamePlayerCharacter,
	vitalEntityVectorNameNPC,
	vitalEntityVectorNameVitalEntity,
	vitalEntityVectorNameObjects,
	vitalEntityVectorNameCount
};



class MobaViewState : public BasicGameViewState
{
protected:
	GameConfiguration * m_gameConfiguration;


	GameAssetFactory m_gameAssetFactory;

	PlayerCharacterViewFactory m_playerCharacterViewFactory;
	NPCViewFactory m_npcViewFactory;
	CharacterViewFactory m_characterViewFactory;
	ActorViewFactory m_actorViewFactory;
	AbilityViewFactory m_abilityViewFactory;
	BuffViewFactory m_buffViewFactory;
	ItemViewFactory m_itemViewFactory;
	GameMapViewFactory m_gameMapViewFactory;

	StandardMatch5v5State * gameState;
	int m_loadProgress;

	KeybindData m_keybindData;

	IndicatorController m_indicatorController;
	InfoPanelController m_infoPanelController;
	TooltipController m_tooltipController;

	DialogScreenController m_dialogScreenController;
	DialogBehaviorIO m_dialogBehaviorViewIO;

	GameCursor m_cursor;
	UIMobaHud m_mobaHud;//derived from UIArea
	UIMobaMap m_mobaMap;

	StatPanel m_statPanel;
	

	LMVector2 m_gameShopOrigin;
	LMVector2 m_gameShopSize;


	GameShopMenu m_gameShopMenu;
	GameMainMenu m_mainMenu;
	UIKeyDialog m_keyDialog;
	
	
	GameMessage m_gameMessage;


	vector<InputModel*> m_inputModelList;

	CameraInputModel m_cameraInputModel;
	CharacterInputModel m_characterInputModel;
	ChatTextAreaInputModel m_chatTextAreaInputModel;
	DevInputModel m_devInputModel;
	EditorInputModel m_editorInputModel;
	InterfaceInputModel m_interfaceInputModel;
	KeyDialogInputModel m_keyDialogInputModel;
	MainMenuInputModel m_mainMenuInputModel;
	ShopMenuInputModel m_shopMenuInputModel;

	vector <HealthBar *> m_pcHealthBars;
	vector <HealthBar *> m_npcHealthBars;
	vector <HealthBar *> m_chestHealthBars;
	vector <HealthBar *> m_objectHealthBars;

	BoidstormView m_boidstormView;




	vector<ShopInventoryView *> m_allShopViews;

	PlayerCharacterView * m_controlledPlayerView;

	vector<vector <PlayerCharacterView*>> m_playerTeams;


	vector <PlayerCharacterView*> m_playerCharacterViews;
	vector <NPCView*> m_npcViews;

	//game sprite (asset) view

	GameMapView * m_gameMapView;//made using new

	//SpriteView m_groundView;
	
	//vector <SpriteView*> m_wallViews;
	vector <VitalEntityView*> m_vitalEntityViews;

	//Quest View

	// QuestView (TODO THIS IS FOR GAME MODE ONLY)
	QuestView m_owlQuestView;

	vector<QuestView *> m_questViews; //quest models only?



	//game Vital (Asset) view

	bool m_isHealthMirrorOn;

	static string m_avatarPath[characterNameCount];

public:
	//interface stuff
	// m_UXTinyFont, m_UXFont, m_UXFontLevel, m_messageFont, m_smallSerif;

	//Theme Profiles
	ThemeResources m_theme;

public:
	MobaViewState();
	~MobaViewState();

	bool Init(GameConfiguration * gameConfiguration);

	bool InitSelectedPhase(int initPhase);
	string GetInitPhaseString(int initPhase);



	bool InitTheme(int theme);
	bool InitDialog(Language language);

	void SubscribeMembersToDamageControllerEvents();

	vector<PlayerCharacterView*> * GetOpponentTeamViews();
	vector<PlayerCharacterView*> * GetPlayerTeamViews();
	vector<PlayerCharacterView*> * GetTeamForSide(TeamName name);

	vector<PlayerCharacterView*> * GetNeutralTeamViews();






	//these are view class managers (should rename or refactor).
	IndicatorController * GetIndicatorController();
	InfoPanelController * GetInfoPanelController();
	TooltipController * GetTooltipController();
	DialogScreenController * GetDialogScreenController();

	//note: cant do one big render (render is ordered with render settings changed between different classes orders etc).
	vector <PlayerCharacterView*> * GetPlayerCharacterViews();
	vector <NPCView*> * GetNPCViews();
	//vector <SpriteView*> * GetWallViews();
	vector <VitalEntityView*> * GetVitalEntityViews();
	
	//SpriteView * GetGroundView();
	GameMapView * GetGameMapView();


	vector<QuestView*> * GetQuestViews();

	BoidstormView * GetBoidstormView();

	GameCursor * GetGameCursor();

	UIMobaHud * GetHud();

	StatPanel * GetStatPanel();
	
	GameShopMenu * GetGameShopMenu();
	GameMainMenu * GetMainMenu();
	UIKeyDialog * GetKeyDialog();
	
	GameMessage * GetGameMessage();

	vector <HealthBar *> * GetHealthBarsByType(VitalEntityVectorName name);
	bool * GetIsHealthMirrorOn();

	CameraInputModel	* GetCameraInputModel();
	CharacterInputModel * GetCharacterInputModel();
	DevInputModel		* GetDevInputModel();
	EditorInputModel	* GetEditorInputModel();
	InterfaceInputModel * GetInterfaceInputModel();
	KeyDialogInputModel	* GetKeyDialogInputModel();
	MainMenuInputModel	* GetMainMenuInputModel();
	ShopMenuInputModel	* GetShopMenuInputModel();
	ChatTextAreaInputModel	* GetChatTextAreaInputModel();

	PlayerCharacterView * GetControlledPlayerView();
	void SetControlledPlayerView(PlayerCharacterView * controlledPlayerView);

	void ActionSetControlledPlayerView(int i);

	void SetGameModel(StandardMatch5v5State * gameStateIn); //gameStateIn,

	

};

#endif