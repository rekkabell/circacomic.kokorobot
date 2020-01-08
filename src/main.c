#include <ctype.h>
#include <stdio.h>
#include <string.h>

int chapters[] = {4, 5, 6, 7, 8};

char *html_head = "<!DOCTYPE html><html lang='en'><head><meta charset='utf-8'><meta name='description' content='Grim Grains is an illustrated food blog, it features plant-based (vegan) recipes.'><meta name='viewport' content='width=device-width, initial-scale=1.0'><meta name='twitter:card' content='summary'><meta name='twitter:site' content='@RekkaBell'><meta name='twitter:title' content='Grimgrains'><meta name='twitter:description' content='An illustrated food blog.'><meta name='twitter:creator' content='@RekkaBell'><meta name='twitter:image' content='https://grimgrains.com/media/services/icon.jpg'><meta property='og:title' content='Grimgrains'><meta property='og:type' content='article'><meta property='og:url' content='http://grimgrains.com/'><meta property='og:image' content='https://grimgrains.com/media/services/icon.jpg'><meta property='og:description' content='An illustrated food blog.'><meta property='og:site_name' content='Grimgrains'><title>Circa — Chapter %d Page %d</title><link rel='stylesheet' type='text/css' href='../links/main.css'></head><body>";

char *html_header = "<header><a href='%s.html'><img src='../media/interface/circa.logo.jpg'></a></header>";

char *html_nav = "<nav><ul><li><a href='%s.html'>Back</a></li><li><a href='%s.html'>Home</a></li><li><a href='%s.html'>Next</a></li></ul></nav>";

char *html_entry = "<main><img src='../media/entries/%s.jpg'/></main>";

char *html_story = "<div class='story'><h2>Story</h2><p>Circa follows Montore's booming gang culture, during a time when tensions between humans and hegatas, descendants of beings whose existence predates that of humans, are high. Sy Cross thrives in climates like this, but things change when the fight hits a little too close to home.</p></div>";

char *html_characters = "<div class='characters'><h2>Characters</h2><img src='../media/content/yegon.png'><img src='../media/content/seir.png'><img src='../media/content/adelie.png'></div>";

char *html_about = "<div class='about'><h2>About</h2><p> This webcomic was designed to reduce the energy use associated with consuming online entertainment. It is drawn by hand, scanned and edited digitally using open-source software (<a href='https://www.gimp.org/'>GIMP</a> and <a href='https://krita.org/en/'>Krita</a>) on Linux, I then apply an image compression technique called “<a href='https://homebrewserver.club/low-tech-website-howto.html#software'>dithering</a>”. Compressed through dithering, images featured on this website are ten times less resource-intensive. Why make a low-tech comic? Read about it <b><a href='https://solar.lowtechmagazine.com/2015/10/can-the-internet-run-on-renewable-energy/'>here</a></b>.</p></div>";

char *html_footer = "<footer><a href='about.html'>Grimgrains</a> © 2014—2020<br><a href='http://100r.co/' target='_blank'>Hundred Rabbits</a></footer></body></html>";

//

int find_prev_chapter(int ch, int pg) {
  if (ch == 0 && pg == 0) {
    return 0;
  }
  if (ch > 0 && pg == 0) {
    return ch - 1;
  }
  return ch;
}

int find_prev_page(int ch, int pg) {
  if (ch == 0 && pg == 0) {
    return 0;
  }
  if (ch > 0 && pg == 0) {
    return chapters[ch - 1] - 1;
  }
  return pg - 1;
}

int find_next_chapter(int ch, int pg) {
  int ch_last = (sizeof chapters / sizeof chapters[0]) - 1;
  int pg_last = chapters[ch];
  if (ch == ch_last && pg == pg_last) {
    return ch_last;
  }
  if (ch < ch_last && pg == pg_last - 1) {
    return ch + 1;
  }
  return ch;
}

int find_next_page(int ch, int pg) {
  int ch_last = (sizeof chapters / sizeof chapters[0]) - 1;
  int pg_last = chapters[ch];
  if (ch == ch_last && pg == pg_last - 1) {
    return pg_last - 1;
  }
  if (ch < ch_last && pg == pg_last - 1) {
    return 0;
  }
  return pg + 1;
}

void build_page(int ch, int pg, char *filename) {
  int ch_prev = find_prev_chapter(ch, pg);
  int pg_prev = find_prev_page(ch, pg);
  int ch_next = find_next_chapter(ch, pg);
  int pg_next = find_next_page(ch, pg);

  printf("%s [%d %d < - > %d %d]\n", filename, ch_prev, pg_prev, ch_next, pg_next);

  char filepath[32];
  snprintf(filepath, 32, "../site/%s.html", filename);
  FILE *myfile = fopen(filepath, "w");

  int ch_home = (sizeof chapters / sizeof chapters[0]) - 1;
  int pg_home = chapters[ch_home] - 1;

  char here_link[32];
  snprintf(here_link, 32, "chapter_%02d_page_%02d", ch + 1, pg + 1);
  char prev_link[32];
  snprintf(prev_link, 32, "chapter_%02d_page_%02d", ch_prev + 1, pg_prev + 1);
  char home_link[32];
  snprintf(home_link, 32, "chapter_%02d_page_%02d", ch_home + 1, pg_home + 1);
  char next_link[32];
  snprintf(next_link, 32, "chapter_%02d_page_%02d", ch_next + 1, pg_next + 1);

  fprintf(myfile, html_head, ch + 1, pg + 1);
  fprintf(myfile, html_header, home_link);
  fprintf(myfile, html_nav, prev_link, home_link, next_link);

  fprintf(myfile, html_entry, here_link);
  fputs(html_story, myfile);
  fputs(html_characters, myfile);
  fputs(html_about, myfile);

  fputs(html_footer, myfile);
  fclose(myfile);
}

int main(void) {
  int chapters_len = sizeof chapters / sizeof chapters[0];
  printf("%d\n", chapters_len);

  for (int ch = 0; ch < chapters_len; ++ch) {
    for (int pg = 0; pg < chapters[ch]; ++pg) {
      char filename[32];
      snprintf(filename, 32, "chapter_%02d_page_%02d", ch + 1, pg + 1);
      build_page(ch, pg, filename);
    }
  }
  
  build_page(chapters_len - 1, chapters[chapters_len - 1], "home");

  return (0);
}
