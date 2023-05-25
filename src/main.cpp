#include "SDL2_gfxPrimitives.h"
#include "application_ui.h"
#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <vector>

using namespace std;

#define EPSILON 0.0001f

struct Coords 
{
  int x, y;

  bool operator==(const Coords &other) const { return x == other.x and y == other.y; }
};

struct Segment 
{
  Coords p1, p2;

  bool operator==(const Segment &other) const
  {
    return ((p1 == other.p1 && p2 == other.p2) ||
            (p1 == other.p2 && p2 == other.p1));
  }

  bool operator!=(const Segment& other) const 
  {
      return !(*this == other);
  }
};

struct Triangle 
{
  Coords p1, p2, p3;
  bool complet = false;
};

struct Application 
{
  int width, height;
  Coords focus{100, 100};

  std::vector<Coords> points;
  std::vector<Triangle> triangles;
};

// changement => trie par x
bool compareCoords(Coords point1, Coords point2) 
{
  // Si les points x sont égaux, alors on les distingue selon leur point y
  if (point1.x == point2.x)
    return point1.y < point2.y;
  return point1.x < point2.x;
}

void drawPoints(SDL_Renderer *renderer, const std::vector<Coords> &points) 
{
  for (std::size_t i = 0; i < points.size(); i++) {
    filledCircleRGBA(renderer, points[i].x, points[i].y, 3, 240, 240, 23,
                     SDL_ALPHA_OPAQUE);
  }
}

void drawSegments(SDL_Renderer *renderer,
                  const std::vector<Segment> &segments) 
{
  for (std::size_t i = 0; i < segments.size(); i++) {
    lineRGBA(renderer, segments[i].p1.x, segments[i].p1.y, segments[i].p2.x,
             segments[i].p2.y, 240, 240, 20, SDL_ALPHA_OPAQUE);
  }
}

void drawTriangles(SDL_Renderer *renderer,
                   const std::vector<Triangle> &triangles) 
{
  for (std::size_t i = 0; i < triangles.size(); i++) {
    const Triangle &t = triangles[i];
    trigonRGBA(renderer, t.p1.x, t.p1.y, t.p2.x, t.p2.y, t.p3.x, t.p3.y, 0, 240,
               160, SDL_ALPHA_OPAQUE);
  }
}

/* ********** D  R  A  W  ********** */

void draw(SDL_Renderer *renderer, const Application &app) {
  /* Remplissez cette fonction pour faire l'affichage du jeu */
  int width, height;
  SDL_GetRendererOutputSize(renderer, &width, &height);

  drawPoints(renderer, app.points);
  drawTriangles(renderer, app.triangles);
}

/*
   Détermine si un point se trouve dans un cercle définit par trois points
   Retourne, par les paramètres, le centre et le rayon
*/
bool CircumCircle(float pX, float pY, float x1, float y1, float x2, float y2,
                  float x3, float y3, float *xc, float *yc, float *rsqr) 
{
  float m1, m2, mx1, mx2, my1, my2;
  float dx, dy, drsqr;
  float fabsy1y2 = fabs(y1 - y2);
  float fabsy2y3 = fabs(y2 - y3);

  /* Check for coincident points */
  if (fabsy1y2 < EPSILON && fabsy2y3 < EPSILON)
    return (false);

  if (fabsy1y2 < EPSILON) {
    m2 = -(x3 - x2) / (y3 - y2);
    mx2 = (x2 + x3) / 2.0;
    my2 = (y2 + y3) / 2.0;
    *xc = (x2 + x1) / 2.0;
    *yc = m2 * (*xc - mx2) + my2;
  } else if (fabsy2y3 < EPSILON) {
    m1 = -(x2 - x1) / (y2 - y1);
    mx1 = (x1 + x2) / 2.0;
    my1 = (y1 + y2) / 2.0;
    *xc = (x3 + x2) / 2.0;
    *yc = m1 * (*xc - mx1) + my1;
  } else {
    m1 = -(x2 - x1) / (y2 - y1);
    m2 = -(x3 - x2) / (y3 - y2);
    mx1 = (x1 + x2) / 2.0;
    mx2 = (x2 + x3) / 2.0;
    my1 = (y1 + y2) / 2.0;
    my2 = (y2 + y3) / 2.0;
    *xc = (m1 * mx1 - m2 * mx2 + my2 - my1) / (m1 - m2);
    if (fabsy1y2 > fabsy2y3) {
      *yc = m1 * (*xc - mx1) + my1;
    } else {
      *yc = m2 * (*xc - mx2) + my2;
    }
  }

  dx = x2 - *xc;
  dy = y2 - *yc;
  *rsqr = dx * dx + dy * dy;

  dx = pX - *xc;
  dy = pY - *yc;
  drsqr = dx * dx + dy * dy;

  return ((drsqr - *rsqr) <= EPSILON ? true : false);
}

/* ICI - ESPACE TRAVAIL*/

void delaunay(Application &app) 
{
  /* --- Trier les points selon x ---*/
  std::sort(app.points.begin(), app.points.end(), compareCoords);

  printf("\n\nAfter sorting vector : ");
  for (auto i = app.points.begin(); i < app.points.end(); i++) 
  {
    cout << "\n(" << i->x << ";" << i->y << ")" << endl;
  }

  /* --- Vider la liste existante de triangles ---*/
  app.triangles.clear();

  /* --- Créer un très grand triangle ---*/
  Triangle *big = new Triangle(
      {Coords{-1000, (-1000)}, Coords{500, 3000}, Coords{1500, -1000}});
  // on l'ajoute aux triangles
  app.triangles.push_back(*big);

  /* --- pour chaque point P du repère --- */
  for (auto _pt1 = app.points.begin(); _pt1 < app.points.end(); _pt1++) 
  {
    /* --- créer une liste de segments LS --- */
    vector<Segment> segments;

    /* --- chaque triangle T déjà créé --- */

    for (auto _triangle = app.triangles.begin();
         _triangle < app.triangles.end();) 
    {
      float xCircle, yCircle, rCircle;
      // si le cercle circonscrit contient le point P alors
      if(CircumCircle(_pt1->x, _pt1->y, _triangle->p1.x, _triangle->p1.y,
                   _triangle->p2.x, _triangle->p2.y, _triangle->p3.x,
                   _triangle->p3.y, &xCircle, &yCircle, &rCircle))
      {
        // Récupérer les différents segments de ce triangles dans LS
        segments.push_back({_triangle->p1, _triangle->p2});
        segments.push_back({_triangle->p2, _triangle->p3});
        segments.push_back({_triangle->p3, _triangle->p1});
        
        // Effacer le triangle de la liste
        _triangle = app.triangles.erase(_triangle);

      }
      else
      {
        ++_triangle;
      }
    }


    // pour chaque segment S de la liste LS faire
    // si un segment est le doublon d'un autre les virer
    for (auto _s1 = segments.begin(); _s1 != segments.end();)
    {
      bool erase_s1 = false;

      for (auto _s2 = segments.begin(); _s2 != segments.end();)
      {
        if (_s1 == _s2)
        {
          ++_s2;
          continue;
        }

        if (_s1->p1 == _s2->p2 && _s1->p2 == _s2->p1)
        {
          _s2 = segments.erase(_s2);
          erase_s1 = true;
        }
        else
        {
          ++_s2;
        }
      }

      if (erase_s1)
      {
        _s1 = segments.erase(_s1);
      }
      else
      {
        ++_s1;
      }
    }


    // pour chaque segment S de la liste LS faire
    for (const Segment& _seg : segments)
    {
      // créer un nouveau triangle composé du segment S et du point P
      app.triangles.push_back({_seg.p1, _seg.p2, {_pt1->x, _pt1->y}});  
    }
  }
}

void construitVoronoi(Application &app) { delaunay(app); }

bool handleEvent(Application &app) 
{
  /* Remplissez cette fonction pour gérer les inputs utilisateurs */
  SDL_Event e;
  while (SDL_PollEvent(&e)) 
  {
    if (e.type == SDL_QUIT)
      return false;
    else if (e.type == SDL_WINDOWEVENT_RESIZED) 
    {
      app.width = e.window.data1;
      app.height = e.window.data1;
    } 
    else if (e.type == SDL_MOUSEWHEEL) 
    {
    } 
    else if (e.type == SDL_MOUSEBUTTONUP) 
    {
      if (e.button.button == SDL_BUTTON_RIGHT) 
      {
        app.focus.x = e.button.x;
        app.focus.y = e.button.y;
        app.points.clear();
      } 
      else if (e.button.button == SDL_BUTTON_LEFT) 
      {
        app.focus.y = 0;
        // Création de points
        app.points.push_back(Coords{e.button.x, e.button.y});
        construitVoronoi(app);
      }
    }
  }
  return true;
}

int main(int argc, char **argv) 
{
  SDL_Window *gWindow;
  SDL_Renderer *renderer;
  Application app{1920, 1080, Coords{0, 0}};
  bool is_running = true;

  // Creation de la fenetre
  gWindow = init("Awesome Voronoi", 1920, 1080);

  if (!gWindow) 
  {
    SDL_Log("Failed to initialize!\n");
    exit(1);
  }

  renderer = SDL_CreateRenderer(gWindow, -1, 0); // SDL_RENDERER_PRESENTVSYNC

  /* **********  G A M E   L O O P ********** */
  while (true) 
  {
    // INPUTS
    is_running = handleEvent(app);
    if (!is_running)
      break;

    // EFFACAGE FRAME
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // DESSIN
    draw(renderer, app);

    // VALIDATION FRAME
    SDL_RenderPresent(renderer);

    // PAUSE en ms
    SDL_Delay(1000 / 30);
  }

  // Free resources and close SDL
  close(gWindow, renderer);

  return 0;
}