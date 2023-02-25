#include "Gui/IntroPanel.h"
#include <iostream>
#include "Events/EventManager.h"
#include "GameUtilities/Event/Events/OnPlaySound.h"
#include "States/StateId.h"
#include <GameUtilities/Event/Events/OnPushState.h>
#include <GameUtilities/Event/Events/Mouse/OnClick.h>
#include "Gui/GuiId.h"


namespace Gui
{

    IntroPanel::IntroPanel()
    {
        //Create start button
        start = tgui::Button::create();
        start->setText("Start");
        start->onPress([](){
            EventManager::inst().post<GU::Evt::OnClick>(Gui::id::START);
       });

        tgui::HorizontalLayout::Ptr startLayout = tgui::HorizontalLayout::create();
        startLayout->addSpace(1);
        startLayout->add(start);
        startLayout->addSpace(1);
        getContentPane()->append(startLayout);

        getContentPane()->appendSpace();

        //Create MultiPlayer button
        multiPlayer = tgui::Button::create();
        multiPlayer->setText("Multiplayer");
        multiPlayer->onPress([](){
            EventManager::inst().post<GU::Evt::OnClick>(Gui::id::MULTIPLAYER);
        });

        tgui::HorizontalLayout::Ptr multiplayerLayout = tgui::HorizontalLayout::create();
        multiplayerLayout->addSpace(1);
        multiplayerLayout->add(multiPlayer);
        multiplayerLayout->addSpace(1);
        getContentPane()->append(multiplayerLayout);

        getContentPane()->appendSpace();

        //Create Options button
        options = tgui::Button::create();
        options->setText("Options");
        options->onPress([](){
            EventManager::inst().post<GU::Evt::OnClick>(Gui::id::OPTIONS);
        });
  
        tgui::HorizontalLayout::Ptr optionLayout = tgui::HorizontalLayout::create();
        optionLayout->addSpace(1);
        optionLayout->add(options);
        optionLayout->addSpace(1);
        getContentPane()->append(optionLayout);
        getContentPane()->appendSpace();
        
        //Create license button
        license = tgui::Button::create();
        license->setText("License");
        license->onPress([](){
            //EventManager::inst().post<GU::Evt::OnClick>(Gui::id::CREDITS);
        });

        tgui::HorizontalLayout::Ptr licenseLayout = tgui::HorizontalLayout::create();
        licenseLayout->addSpace(1);
        licenseLayout->add(license);
        licenseLayout->addSpace(1);
        getContentPane()->append(licenseLayout);
        getContentPane()->appendSpace();
        
        //Create credits button
        credits = tgui::Button::create();
        credits->setText("Credits");
        credits->onPress([](){
            EventManager::inst().post<GU::Evt::OnClick>(Gui::id::CREDITS);
        });

        tgui::HorizontalLayout::Ptr creditsLayout = tgui::HorizontalLayout::create();
        creditsLayout->addSpace(1);
        creditsLayout->add(credits);
        creditsLayout->addSpace(1);
        getContentPane()->append(creditsLayout);
        getContentPane()->appendSpace();
        

        //Create exit button
        exit = tgui::Button::create();
        exit->setText("Exit");
        exit->onPress([](){
            EventManager::inst().post<GU::Evt::OnClick>(Gui::id::EXIT);
        });

        tgui::HorizontalLayout::Ptr exitLayout = tgui::HorizontalLayout::create();
        exitLayout->addSpace(1);
        exitLayout->add(exit);
        exitLayout->addSpace(1);
        getContentPane()->append(exitLayout);
    }

    
    void IntroPanel::init(const int &width, const int &height)
    {
        this->setSize(width / 2, height / 2);
        this->setPosition(width / 4, height / 4);
    }

    IntroPanel::~IntroPanel()
    {
        //dtor
    }
}
