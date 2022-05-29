#include "Game.h"
#include "GameObjectFactory.h"
#include "StateParser.h"
#include "TextureManager.h"
#include "logging.h"

bool StateParser::parseState(const char *stateFile, std::string stateID, std::vector<GameObject *> *pObjects,  std::vector<std::string> *textures)
{
    tinyxml2::XMLDocument xmlDoc;

    if (xmlDoc.LoadFile(stateFile) != tinyxml2::XML_SUCCESS) {
        ERROR(xmlDoc.ErrorStr());
        return false;
    }

    tinyxml2::XMLElement *pRoot = xmlDoc.RootElement();
    tinyxml2::XMLElement *pStateRoot = 0;

    for (tinyxml2::XMLElement *e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == stateID) {
            pStateRoot = e;
            break;
        }
    }

    if (pStateRoot == 0) {
        return false;
    }

    tinyxml2::XMLElement *texturesRoot = 0;
    for (auto e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("TEXTURES")) {
            texturesRoot = e;
            break;
        }
    }

    parseTextures(texturesRoot, textures);

    tinyxml2::XMLElement *pObjectsRoot = 0;
    for (auto e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("OBJECTS")) {
            pObjectsRoot = e;
			break;
        }
    }

    parseObjects(pObjectsRoot, pObjects);

    return true;
}

void StateParser::parseTextures(tinyxml2::XMLElement *pStateRoot, std::vector<std::string> *pTextureIDs) {
    for (auto e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        std::string filenameAttribute = e->Attribute("filename");
        std::string idAttribute = e->Attribute("ID");

        pTextureIDs->push_back(idAttribute);

        TextureManager::Instance()->load(filenameAttribute, idAttribute, Game::Instance()->getRenderer());
    }
}

void StateParser::parseObjects(tinyxml2::XMLElement *pStateRoot, std::vector<GameObject *> *pObjects) {
    for (auto e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        int x, y, width, height, numFrames, callbackID, animateSpeed;
        std::string textureID;

        x = e->IntAttribute("x");
        y = e->IntAttribute("y");
        width = e->IntAttribute("width");
        height = e->IntAttribute("height");
        numFrames = e->IntAttribute("numFrames");
        callbackID = e->IntAttribute("callbackID");
        animateSpeed = e->IntAttribute("animateSpeed");

        textureID = e->Attribute("textureID");

        GameObject* pGameObject = GameObjectFactory::Instance()->create(e->Attribute("type"));

        pGameObject->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animateSpeed)));

        pObjects->push_back(pGameObject);
    }
}