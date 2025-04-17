#include <iostream>
#include <fstream>
#include "renderText.h"
#include "renderImage.h"
#include "logic.h"
#include "loadMixer.h"

vector <Question> questions;
vector<Question> readQuestionsFromFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string temp;
        while (getline(file,temp)) {
            Question q;
            q.question = temp;
            getline(file, q.answerA);
            getline(file, q.answerB);
            getline(file, q.answerC);
            getline(file, q.answerD);
            file >> q.correctAnswer;
            file.ignore(); // Bỏ qua kí tự xuống dòng thừa
            questions.push_back(q);
        }
        file.close();
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
    return questions;
}
int checkAnswer(int x, int y , const Question &q)
{
    char answer;
    if (x >= answer1X && x <= answer1X + 600 && y >= answer1Y && y <= answer1Y + 60)
    {
       answer = 'a';
       if (answer == q.correctAnswer)  return 1;
       return 0;
    }
    if (x >= answer2X && x <= answer2X + 600 && y >= answer2Y && y <= answer2Y + 60)
    {
       answer = 'b';
       if (answer == q.correctAnswer)  return 1;
        return 0;
    }
    if (x >= answer3X && x <= answer3X + 600 && y >= answer3Y && y <= answer3Y + 60)
    {
       answer = 'c';
       if (answer == q.correctAnswer)  return 1;
        return 0;
    }
    if (x >= answer4X && x <= answer4X + 600 && y >= answer4Y && y <= answer4Y + 60)
    {
       answer = 'd';
       if (answer == q.correctAnswer)  return 1;
       return 0;
    }
   return 2;
}
void showQuestionAndAnswer(SDL_Window *window, SDL_Renderer *renderer, const Question &q)
{
    renderText(window, renderer, q.question, 100, 85, fontSize);
    renderText(window, renderer, q.answerA, answer1X + 40, answer1Y, fontSize);
    renderText(window, renderer, q.answerB, answer2X + 40, answer2Y, fontSize);
    renderText(window, renderer, q.answerC, answer3X + 40, answer3Y, fontSize);
    renderText(window, renderer, q.answerD, answer4X + 40, answer4Y, fontSize);
}

void playGames(SDL_Window *window, SDL_Renderer *renderer, int score, int LIFE)
{
    int QNo = 0;
    questions = readQuestionsFromFile("questions.txt");
    while (LIFE > 0 && QNo < 10) {
        int randomIndex = rand() % questions.size();
        showImagines(window, renderer);
        showScore(window, renderer, score, LIFE);
        showQuestionAndAnswer(window, renderer, questions[randomIndex]);
        SDL_RenderPresent(renderer);
        SDL_Event e;
        while (true)
        {
            SDL_Delay(10);
        // Nếu không có sự kiện gì thì tiếp tục trở về đầu vòng lặp
        if ( SDL_WaitEvent(&e) == 0) continue;

        // Nếu sự kiện là kết thúc (như đóng cửa sổ) thì thoát khỏi vòng lặp
        if (e.type == SDL_QUIT) break;

        // Nếu nhấn phím ESC thì thoát khỏi vòng lặp
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
        // Nếu chuột (mouse) được nhấn (xuống)
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX = e.button.x; // Lấy hoành độ x của chuột
            int mouseY = e.button.y; // Lấy tung độ y của chuột
            if (checkAnswer(mouseX, mouseY, questions[randomIndex]) == 1)
            {
                score +=10;
                player_answer(window, renderer, 1);
                SDL_RenderPresent(renderer);
                playShortSound("sounds/correctAnswer.mp3", 0);
                SDL_Delay(1000);
                break;
            } else if (checkAnswer(mouseX, mouseY, questions[randomIndex]) == 0){
                LIFE --;
                player_answer(window, renderer, 0);
                SDL_RenderPresent(renderer);
                playShortSound("sounds/wrongAnswer.mp3", 0);
                SDL_Delay(1000);
                break;
            }
        }
    }
    questions.erase(questions.begin() + randomIndex);
    QNo ++;
    }
    SDL_RenderClear(renderer);
    GameOver(window, renderer, score);
}
void GameOver(SDL_Window *window, SDL_Renderer *renderer, int finalScore)
{
    showEndGames(window, renderer);
    // Vẽ điểm số cuối cùng
    string scoreText = "Final Score: " + to_string(finalScore);
    renderText(window, renderer, scoreText, 600, 250, 80);
    SDL_RenderPresent(renderer);
    if (finalScore <= 40){playShortSound("sounds/gameOver.mp3", 0);}
    else {playShortSound("sounds/winGames.mp3", 0);}
     // Vẽ tùy chọn chơi lại hoặc thoát trò chơi
    SDL_Event e;
    while (true)
    {
        SDL_Delay(10);
        // Nếu không có sự kiện gì thì tiếp tục trở về đầu vòng lặp
        if ( SDL_WaitEvent(&e) == 0) continue;

        // Nếu sự kiện là kết thúc (như đóng cửa sổ) thì thoát khỏi vòng lặp
        if (e.type == SDL_QUIT) break;

        // Nếu nhấn phím ESC thì thoát khỏi vòng lặp
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
        // Nếu chuột (mouse) được nhấn (xuống)
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX = e.button.x; // Lấy hoành độ x của chuột
            int mouseY = e.button.y; // Lấy tung độ y của chuột
            if (mouseX >= 950 && mouseX <= 1170 && mouseY >= 450 && mouseY <= 510)
            {
                SDL_Quit();
            }
            if (mouseX >= 570 && mouseX <= 870 && mouseY >= 450 && mouseY <= 510)
            {
                playGames(window, renderer, 0, 3);
            }
        }
    }
}
