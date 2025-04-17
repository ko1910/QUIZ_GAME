#ifndef LOGIC_H_
#define LOGIC_H_

#include <SDL.h>
#include <vector>
#include "renderImage.h"

using namespace std;

struct Question
{
    string question;
    string answerA;
    string answerB;
    string answerC;
    string answerD;
    char correctAnswer;
};

vector<Question> readQuestionsFromFile(const string& filename);
int checkAnswer(int x, int y , const Question &q);
void showQuestionAndAnswer(SDL_Window *window, SDL_Renderer *renderer, const Question &q);
void playGames(SDL_Window *window, SDL_Renderer *renderer, int score, int LIFE);
void GameOver(SDL_Window *window, SDL_Renderer *renderer, int finalScore);
#endif // LOGIC_H_
