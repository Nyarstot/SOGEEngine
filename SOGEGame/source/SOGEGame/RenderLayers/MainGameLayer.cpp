#include "SOGEGame/RenderLayers/MainGameLayer.hpp"

void MainGameLayer::UpdateScore(bool aSide)
{
    // true - player
    // false - enemy

    if (aSide == true) mPlayer->EncreaseScore();
    else mEnemy->EncreaseScore();

    int playerScore = mPlayer->GetScore();
    int enemyScore = mEnemy->GetScore();

    mGraphicsPlayerScore = std::to_wstring(playerScore);
    mGraphucsEnemyScore = std::to_wstring(enemyScore);

    mPlayerFontDescriptor.color = dx::Colors::White;
    mEnemyFontDescriptor.color = dx::Colors::White;

    if (playerScore > enemyScore) {
        mPlayerFontDescriptor.color = dx::Colors::Green;
        mEnemyFontDescriptor.color = dx::Colors::Red;
    }
    else if (playerScore < enemyScore) {
        mPlayerFontDescriptor.color = dx::Colors::Red;
        mEnemyFontDescriptor.color = dx::Colors::Green;
    }
}

MainGameLayer::MainGameLayer()
    : Layer("MainGameLayer")
{
    mPlayer = Player::CreateUnique();
    mEnemy = Enemy::CreateUnique();
    mBall = Ball::CreateUnique();

    mEnemyCounter = soge::SpriteFont::CreateUnique(L"fonts/sample.spritefont");
    mPlayerCounter = soge::SpriteFont::CreateUnique(L"fonts/sample.spritefont");

    mPlayerFontDescriptor.position = { 550.0f, 0.0f };
    mEnemyFontDescriptor.position = { 650.0f, 0.0f };
}

MainGameLayer::~MainGameLayer()
{
}

void MainGameLayer::OnAttach()
{

}

void MainGameLayer::OnDetach()
{

}

void MainGameLayer::OnUpdate(float aDeltaTime)
{
    if (mBall->IsOutOfBound()) {
        this->UpdateScore(mBall->GetLastBound());
    }

    //mPlayer1Racket->test(aDeltaTime);
    mPlayer->Update(aDeltaTime);
    mEnemy->Update(aDeltaTime, mBall.get());
    mBall->Update(aDeltaTime);

    //mFont->DrawString(L"SAMPLE TEXT", mFontDescriptor1);
    mPlayerCounter->DrawString(mGraphicsPlayerScore.c_str(), mPlayerFontDescriptor);
    mEnemyCounter->DrawString(mGraphucsEnemyScore.c_str(), mEnemyFontDescriptor);

    auto* physEngine = soge::PhysicsEngine::GetInstance();
    physEngine->CollisionTest(mPlayer->GetRacket()->GetCollision(), mBall->GetCollision());
    physEngine->CollisionTest(mEnemy->GetRacket()->GetCollision(), mBall->GetCollision());
}

void MainGameLayer::OnEvent(soge::Event& aEvent)
{
    mPlayer->OnEvent(aEvent);
    mBall->OnEvent(aEvent);
}
