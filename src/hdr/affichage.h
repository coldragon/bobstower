void AfficherBob(SDL_Renderer* render, leBob *BOB);
void CleanScreen(SDL_Renderer* render, int r, int g, int b);
void AfficherMap_layer1(SDL_Renderer* render, Texture* tileset, leMap MAP);
void AfficherMap_layer2(SDL_Renderer* render, Texture* tileset, leMap MAP);
void AfficherObj(SDL_Renderer* render, Texture* objset, leMap MAP1);
void AfficherGui(SDL_Renderer* render, Texture* guiset, leBob *BOB, TTF_Font *police);
