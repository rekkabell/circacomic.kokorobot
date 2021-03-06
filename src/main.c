#include <ctype.h>
#include <stdio.h>
#include <string.h>

int chapters[] = {13,14};

char *html_head = "<!DOCTYPE html><html lang='en'><head><meta charset='utf-8'><meta name='description' content='A tale of ancient demons and monkeywrenching.'><meta name='viewport' content='width=device-width, initial-scale=1.0'><meta name='twitter:card' content='summary'><meta name='twitter:site' content='@RekkaBell'><meta name='twitter:title' content='Circa Comic'><meta name='twitter:description' content='A tale of ancient demons and monkeywrenching.'><meta name='twitter:creator' content='@RekkaBell'><meta name='twitter:image' content='http://circacomic.kokorobot.ca/media/services/icon.jpg'><meta property='og:title' content='Circa Comic'><meta property='og:type' content='article'><meta property='og:url' content='http://circacomic.kokorobot.ca/'><meta property='og:image' content='https://grimgrains.com/media/services/icon.jpg'><meta property='og:description' content='A tale of ancient demons and monkeywrenching.'><meta property='og:site_name' content='Circa Comic'><link rel='icon' type='image/x-icon' href='../media/services/favicon.ico'><link rel='icon' type='image/png' href='../media/services/icon.jpg'><link rel='apple-touch-icon' href='../media/services/apple-touch-icon.png' /><title>Circa — Chapter %d Page %d</title><link rel='stylesheet' type='text/css' href='../links/main.css'></head><body>";

char *html_header = "<header><a href='%s.html'><img src='../media/interface/circa.logo.jpg'></a></header>";

char *html_nav = "<nav><ul><li><a href='%s.html'>back</a></li><li><a href='chapter_01_page_01.html'>first</a></li><li><a href='%s.html'>latest</a></li><li><a href='%s.html'>next</a></li></ul></nav>";

char *html_entry = "<img src='../media/content/%s.png' class='pages'/>";

char *html_story = "<div><p>\"A tale of ancient demons and sabotage. It's about the city of Montore, and humans encroaching on nature, and on the descendants of an ancient race (Hegatas) who fight back. The story is a dark comedy, and follows two gangs: The Solomon's Devils (solo devs) and the Ars Goetia. Both have similar visions of the future, but bicker on how to best build/destroy the road to get there.\"</p></div>";

char *html_characters = "<div><img src='../media/content/ocportraits/yegon.jpg' class='characters'><img src='../media/content//ocportraits/seir.jpg' class='characters'><img src='../media/content/ocportraits/adelie.jpg' class='characters'><img src='../media/content/ocportraits/nemerald.jpg' class='characters'><img src='../media/content/ocportraits/caleb.jpg' class='characters'><img src='../media/content/ocportraits/sy.jpg' class='characters'><img src='../media/content/ocportraits/orion.jpg' class='characters'></div>";

char *html_about = "<div><p>This comic is drawn by hand, scanned and edited digitally using open-source software (<a href='https://www.gimp.org/'>GIMP</a> & <a href='https://krita.org/en/'>Krita</a>) on <b>Linux</b>.</p><br><p><b>Last update: 01-05-21</b>. Updated irregularly. My internet situation isn't always good. Subscribe to the comic's <a href='https://circacomic.kokorobot.ca/links/rss.xml' target='_blank'>rss feed</a></p><br /><p><b>License:</b> The license applies to all the documented projects, the projects themselves and their assets. The website source code is under the <a href='https://github.com/rekkabell/circacomic.kokorobot/blob/master/LICENSE.mit.md' target='_blank'>MIT License</a>. The assets, story, characters and text content are under the <a href='https://github.com/rekkabell/circacomic.kokorobot/blob/master/LICENSE.by-nc-sa-4.0.md' target='_blank'>BY-NC-SA4.0 License</a>.</p></div>";

char *html_footer = "<footer><a href='about.html'>Circa</a> © 2021 <a href='https://creativecommons.org/licenses/by-nc-sa/4.0/' target='_blank'>BY-NC-SA-4.0</a><br><a href='http://kokorobot.ca/' target='_blank'>Rek Bellum</a><br /><br /><a href='https://merveilles.town/@rek' target='_blank'>Mastodon</a> | <a href='https://100r.co' target='_blank'>Hundredrabbits</a> | <a href='https://github.com/rekkabell/circacomic.kokorobot' target='_blank'> Github</a></footer></body></html>";

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

  fputs("<main>", myfile);
  fprintf(myfile, html_entry, here_link);
  fputs(html_story, myfile);
  fputs(html_characters, myfile);
  fputs(html_about, myfile);
  fputs("</main>", myfile);

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
  
  build_page(chapters_len - 1, chapters[chapters_len - 1] - 1, "home");

  return (0);
}
