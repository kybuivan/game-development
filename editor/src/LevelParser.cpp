#include <string>
#include "LevelParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "ObjectLayer.h"
#include "TileLayer.h"
#include "GameObjectFactory.h"
#include "base64.h"
#include "Level.h"
#include "logging.h"

Level* LevelParser::parseLevel(const char *levelFile)
{
    // create the level object
    Level* pLevel = new Level();
    // create a tinyXML document and load the map xml
    tinyxml2::XMLDocument levelDocument;
    
    if (levelDocument.LoadFile(levelFile) != tinyxml2::XML_SUCCESS) {
        ERROR(levelDocument.ErrorStr());
        return pLevel;
    }
    
    // get the root node and display some values
    tinyxml2::XMLElement* pRoot = levelDocument.RootElement();
    
    DEBUG("Loading level:\nVersion: {}", pRoot->Attribute("version"));
    DEBUG("Width:{} - Height:{}", pRoot->Attribute("width"), pRoot->Attribute("height"));
    DEBUG("Tile Width:{} - Tile Height:{}", pRoot->Attribute("tilewidth"),pRoot->Attribute("tileheight"));
    
    m_tileSize = pRoot->IntAttribute("tilewidth");
    m_width = pRoot->IntAttribute("width");
    m_height = pRoot->IntAttribute("height");
    
    //we know that properties is the first child of the root
    tinyxml2::XMLElement* pProperties = pRoot->FirstChildElement();
    
    // we must parse the textures needed for this level, which have been added to properties
    for(tinyxml2::XMLElement* e = pProperties->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("property"))
        {
            parseTextures(e);
        }
    }
    
    // we must now parse the tilesets
    for(tinyxml2::XMLElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("tileset"))
        {
            parseTilesets(e, pLevel->getTilesets());
        }
    }
    
    // parse any object layers
    for(tinyxml2::XMLElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("objectgroup") || e->Value() == std::string("layer"))
        {
            if(e->FirstChildElement()->Value() == std::string("object"))
            {
                parseObjectLayer(e, pLevel->getLayers(), pLevel);
            }
            else if(e->FirstChildElement()->Value() == std::string("data") ||
                    (e->FirstChildElement()->NextSiblingElement() != 0 && e->FirstChildElement()->NextSiblingElement()->Value() == std::string("data")))
            {
                parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets(), pLevel->getCollisionLayers());
            }
        }
    }
    
    return pLevel;
}

void LevelParser::parseTilesets(tinyxml2::XMLElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
    std::string assetsTag = "assets/";
    // first add the tileset to texture manager
    DEBUG("adding texture {}  with ID {}", pTilesetRoot->FirstChildElement()->Attribute("source"), pTilesetRoot->Attribute("name"));
    TextureManager::Instance()->load(assetsTag.append(pTilesetRoot->FirstChildElement()->Attribute("source")), pTilesetRoot->Attribute("name"), Game::Instance()->getRenderer());
    
    // create a tileset object
    Tileset tileset;
    tileset.width = pTilesetRoot->FirstChildElement()->IntAttribute("width");
    tileset.height = pTilesetRoot->FirstChildElement()->IntAttribute("height");
    tileset.firstGridID = pTilesetRoot->IntAttribute("firstgid");
    tileset.tileWidth = pTilesetRoot->IntAttribute("tilewidth");
    tileset.tileHeight = pTilesetRoot->IntAttribute("tileheight");
    tileset.spacing = pTilesetRoot->IntAttribute("spacing");
    tileset.margin = pTilesetRoot->IntAttribute("margin");
    tileset.name = pTilesetRoot->Attribute("name");
    
    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);
    
    pTilesets->push_back(tileset);
}

void LevelParser::parseTileLayer(tinyxml2::XMLElement* pTileElement, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets, std::vector<TileLayer*> *pCollisionLayers)
{
    TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);
    
    bool collidable = false;
    
    // tile data
    std::vector<std::vector<int>> data;
    
    std::string decodeIDs;
    tinyxml2::XMLElement* pDataNode;
    
    for(tinyxml2::XMLElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("properties"))
        {
            for(tinyxml2::XMLElement* property = e->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
            {
                if(property->Value() == std::string("property"))
                {
                    if(property->Attribute("name") == std::string("collidable"))
                    {
                        collidable = true;
                    }
                }
            }
        }
        if(e->Value() == std::string("data"))
        {
            pDataNode = e;
        }
    }
    
    for(tinyxml2::XMLNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling())
    {
        tinyxml2::XMLText* text = e->ToText();
        std::string t = text->Value();
        decodeIDs = base64_decode(t);
    }
    
    if(decodeIDs.empty())
    {
        ERROR("could decore IDs data from xml");
        return;
    }

    unsigned long numGids = m_width * m_height;//* sizeof(int);
    std::vector<unsigned> gids(numGids);
    
    // Fix until i know how base 64 works
    for(int i = 0; i < numGids; i++)
    {    
        gids[i] = (unsigned)(decodeIDs[i * 4]) * 1 +
                  (unsigned)(decodeIDs[(i * 4) + 1]) * 2 +
                  (unsigned)(decodeIDs[(i * 4) + 2]) * 4 +
                  (unsigned)(decodeIDs[(i * 4) + 3]) * 8;
    }

    //uncompress((Bytef*)&gids[0], &numGids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());

    std::vector<int> layerRow(m_width);
    
    for(int j = 0; j < m_height; j++)
    {
        data.push_back(layerRow);
    }
    
    for(int rows = 0; rows < m_height; rows++)
    {
        for(int cols = 0; cols < m_width; cols++)
        {
            data[rows][cols] = gids[rows * m_width + cols];
        }
    }


    pTileLayer->setTileIDs(data);
    pTileLayer->setMapWidth(m_width);
    
    if(collidable)
    {
        pCollisionLayers->push_back(pTileLayer);
    }
    
    pLayers->push_back(pTileLayer);
}

void LevelParser::parseTextures(tinyxml2::XMLElement* pTextureRoot)
{
    DEBUG("adding texture {} with ID {}", pTextureRoot->Attribute("value"), pTextureRoot->Attribute("name"));
    TextureManager::Instance()->load(pTextureRoot->Attribute("value"), pTextureRoot->Attribute("name"), Game::Instance()->getRenderer());
}

void LevelParser::parseObjectLayer(tinyxml2::XMLElement* pObjectElement, std::vector<Layer*> *pLayers, Level* pLevel)
{
    // create an object layer
    ObjectLayer* pObjectLayer = new ObjectLayer();
    
    for(tinyxml2::XMLElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("object"))
        {
            int x, y, width, height, numFrames, callbackID = 0, animateSpeed = 0;
            std::string textureID;
            std::string type;
            
            // get the initial node values type, x and y
            x = e->IntAttribute("x");
            y = e->IntAttribute("y");
            
            type = e->Attribute("type");
            GameObject* pGameObject = GameObjectFactory::Instance()->create(type);
            
            // get the property values
            for(tinyxml2::XMLElement* properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement())
            {
                if(properties->Value() == std::string("properties"))
                {
                    for(tinyxml2::XMLElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
                    {
                        if(property->Value() == std::string("property"))
                        {
                            if(property->Attribute("name") == std::string("numFrames"))
                            {
                                numFrames = property->IntAttribute("value");
                            }
                            else if(property->Attribute("name") == std::string("textureHeight"))
                            {
                                height = property->IntAttribute("value");
                            }
                            else if(property->Attribute("name") == std::string("textureID"))
                            {
                                textureID = property->Attribute("value");
                            }
                            else if(property->Attribute("name") == std::string("textureWidth"))
                            {
                                width = property->IntAttribute("value");
                            }
                            else if(property->Attribute("name") == std::string("callbackID"))
                            {
                                callbackID = property->IntAttribute("value");
                            }
                            else if(e->Attribute("name") == std::string("animateSpeed"))
                            {
                                animateSpeed = property->IntAttribute("value");
                            }
                        }
                    }
                }
            }
            //int x, int y, int width, int height, std::string textureID, int numFrames, void()
            pGameObject->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames,callbackID, animateSpeed)));
            
            if(type == "Player")
            {
                pLevel->setPlayer(dynamic_cast<Player*>(pGameObject));
            }
            
            pObjectLayer->getGameObjects()->push_back(pGameObject);
        }
    }
    
    pLayers->push_back(pObjectLayer);
}