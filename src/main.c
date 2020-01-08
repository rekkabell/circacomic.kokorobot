#include <ctype.h>
#include <stdio.h>
#include <string.h>

int chapters[] = {19, 10, 8, 17, 9};

char *html_head = "<!DOCTYPE html><html lang='en'><head><meta charset='utf-8'><meta name='description' content='Grim Grains is an illustrated food blog, it features plant-based (vegan) recipes.'><meta name='viewport' content='width=device-width, initial-scale=1.0'><meta name='twitter:card' content='summary'><meta name='twitter:site' content='@RekkaBell'><meta name='twitter:title' content='Grimgrains'><meta name='twitter:description' content='An illustrated food blog.'><meta name='twitter:creator' content='@RekkaBell'><meta name='twitter:image' content='https://grimgrains.com/media/services/icon.jpg'><meta property='og:title' content='Grimgrains'><meta property='og:type' content='article'><meta property='og:url' content='http://grimgrains.com/'><meta property='og:image' content='https://grimgrains.com/media/services/icon.jpg'><meta property='og:description' content='An illustrated food blog.'><meta property='og:site_name' content='Grimgrains'><title>Circa — Chapter %d Page %d</title><link rel='stylesheet' type='text/css' href='../links/main.css'></head><body>";

char *html_header = "<header><a href='home.html'><img src='../media/interface/circa.logo.jpg'></a></header>";

char *html_nav = "<nav><ul><li><a href='%s.html'>Back</a></li><li><a href='%s.html'>Home</a></li><li><a href='%s.html'>Next</a></li></ul></nav>";

char *html_story = "<div class='story'><h2>Story</h2><p>Circa follows Montore's booming gang culture, during a time when tensions between humans and hegatas, descendants of beings whose existence predates that of humans, are high. Sy Cross thrives in climates like this, but things change when the fight hits a little too close to home.</p></div>";

char *html_characters = "<div class='characters'><h2>Characters</h2><img src='../media/content/yegon.png'><img src='../media/content/seir.png'><img src='../media/content/adelie.png'></div>";

char *html_about = "<div class='about'><h2>About</h2><p> This webcomic was designed to reduce the energy use associated with consuming online entertainment. It is drawn by hand, scanned and edited digitally using open-source software (<a href='https://www.gimp.org/'>GIMP</a> and <a href='https://krita.org/en/'>Krita</a>) on Linux, I then apply an image compression technique called “<a href='https://homebrewserver.club/low-tech-website-howto.html#software'>dithering</a>”. Compressed through dithering, images featured on this website are ten times less resource-intensive. Why make a low-tech comic? Read about it <b><a href='https://solar.lowtechmagazine.com/2015/10/can-the-internet-run-on-renewable-energy/'>here</a></b>.</p></div>";

char *html_footer = "<footer><a href='about.html'>Grimgrains</a> © 2014—2020<br><a href='http://100r.co/' target='_blank'>Hundred Rabbits</a></footer></body></html>";

void build_page(int ch, int pg, int id, int limit) {
  printf("chapter_%02d_page_%02d %d/%d\n", ch, pg, id, limit);

  char filepath[32];
  snprintf(filepath, 32, "../site/chapter_%02d_page_%02d.html", ch + 1, pg + 1);
  FILE *myfile = fopen(filepath, "w");

  fprintf(myfile, html_head, ch + 1, pg + 1);
  fputs(html_header, myfile);
  fprintf(myfile, html_nav, "back", "home", "next");

  fputs(html_story, myfile);
  fputs(html_characters, myfile);
  fputs(html_about, myfile);

  fputs(html_footer, myfile);
  fclose(myfile);
}

int main(void) {
  int chapters_len = sizeof chapters / sizeof chapters[0];
  printf("%d\n", chapters_len);

  int limit = 0;
  for (int ch = 0; ch < chapters_len; ++ch) {
    limit = limit + chapters[ch];
  }

  int id = 1;
  for (int ch = 0; ch < chapters_len; ++ch) {
    for (int pg = 0; pg < chapters[ch]; ++pg) {
      build_page(ch, pg, id, limit);
      id = id + 1;
    }
  }

  return (0);
}
