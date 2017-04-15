#include "TutorialApplication.h"

TutorialApplication::TutorialApplication(void)
{
}

TutorialApplication::~TutorialApplication(void)
{
}

void TutorialApplication::createScene()
{
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(20, 80, 50);

	//mCamera->setPosition(0, 47, 222);

	std::vector<Ogre::SceneNode*> level;
	level.push_back(mSceneMgr->getRootSceneNode());

	int offset = 0;

	for (int i = 0; i < levels; ++i)
	{	
		std::vector<Ogre::SceneNode*> nextLevel;

		for (auto& node : level)
		{
			for (int child = 0; child < childNodesPerLevel; ++child)
			{
				auto childNode = node->createChildSceneNode(Ogre::Vector3(0,0,offset));
				auto childEntity = mSceneMgr->createEntity("ogrehead.mesh");
				childNode->attachObject(childEntity);
				nextLevel.push_back(childNode);

				offset++;
			}
		}

		level = nextLevel;
	}
}

void TutorialApplication::go()
{
#ifdef _DEBUG
#ifndef OGRE_STATIC_LIB
	mResourcesCfg = m_ResourcePath + "resources_d.cfg";
	mPluginsCfg = m_ResourcePath + "plugins_d.cfg";
#else
	mResourcesCfg = "resources_d.cfg";
	mPluginsCfg = "plugins_d.cfg";
#endif
#else
#ifndef OGRE_STATIC_LIB
	mResourcesCfg = m_ResourcePath + "resources.cfg";
	mPluginsCfg = m_ResourcePath + "plugins.cfg";
#else
	mResourcesCfg = "resources.cfg";
	mPluginsCfg = "plugins.cfg";
#endif
#endif

	resultFile.open("result.txt");

	resultFile << "\\begin{figure}[!ht] \n";
	resultFile << "\\begin{center}\n";

	resultFile << "\t\\begin{tabular}{ | l | l | } \n";
	resultFile << "\t\\hline \n";
	resultFile << "\tNodes(\\#) & Time(ms) \\\\ \\hline \n";

	levels = 1;
	int levels_test = 18;
	childNodesPerLevel = 2;

	BaseApplication::setup();

	for (; levels <= levels_test; levels += 1)
	{
		createScene();
		BaseApplication::go();
		mSceneMgr->clearScene();
	}

	resultFile << "\t\\end{tabular} \n";
	resultFile << "\\end{center}";
	resultFile << "\\caption{empty} \n";
	resultFile << "\\label{figure:empty} \n";
	resultFile << "\\end{figure} \n";

}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go();
        } catch(Ogre::Exception& e)  {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occurred: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
