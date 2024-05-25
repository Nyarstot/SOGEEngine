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
    mGraphicsEnemyScore = std::to_wstring(enemyScore);

    mPlayerCounter->SetFontColor(dx::Colors::White);
    mEnemyCounter->SetFontColor(dx::Colors::White);

    if (playerScore > enemyScore) {
        mPlayerCounter->SetFontColor(dx::Colors::Green);
        mEnemyCounter->SetFontColor(dx::Colors::Red);
    }
    else if (playerScore < enemyScore) {
        mPlayerCounter->SetFontColor(dx::Colors::Red);
        mEnemyCounter->SetFontColor(dx::Colors::Green);
    }
}

MainGameLayer::MainGameLayer()
    : Layer("MainGameLayer")
{
    mPlayer = Player::CreateUnique();
    mEnemy = Enemy::CreateUnique();
    mBall = Ball::CreateUnique();

    mPlayerFontDescriptor.fontFilePath = L"fonts/sample.spritefont";
    mPlayerFontDescriptor.position = { 550.0f, 0.0f };

    mEnemyFontDescriptor.fontFilePath = L"fonts/sample.spritefont";
    mEnemyFontDescriptor.position = { 650.0f, 0.0f };

    mEnemyCounter = soge::SpriteFont::CreateUnique(mEnemyFontDescriptor);
    mPlayerCounter = soge::SpriteFont::CreateUnique(mPlayerFontDescriptor);

    auto deviceContext = soge::Renderer::GetInstance()->GetDeviceContext();
    auto rasterizer = soge::Renderer::GetInstance()->GetRasterizerState();

    mFontBatcher = soge::SpriteBatch::CreateUnique(deviceContext);
    mFontBatcherDescriptor.rasterizerState = rasterizer;
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

    mFontBatcher->Begin(mFontBatcherDescriptor);
    mPlayerCounter->DrawString(mFontBatcher.get(), mGraphicsPlayerScore.c_str());
    mEnemyCounter->DrawString(mFontBatcher.get(), mGraphicsEnemyScore.c_str());
    mFontBatcher->End();

    auto* physEngine = soge::PhysicsEngine::GetInstance();
    physEngine->CollisionTest(mPlayer->GetRacket()->GetCollision(), mBall->GetCollision());
    physEngine->CollisionTest(mEnemy->GetRacket()->GetCollision(), mBall->GetCollision());
}

void MainGameLayer::OnEvent(soge::Event& aEvent)
{
    mPlayer->OnEvent(aEvent);
    mBall->OnEvent(aEvent);
}
