#ifndef CALLBACKS_H
#define CALLBACKS_H

#ifdef __cplusplus
extern "C" {
#endif

	void keyboard(unsigned char key, int x, int y);
	void mouse(int button, int state, int x, int y);
	void drawBez(void);
	void motion(int x, int y);
	void reshape(int w, int h);
	void menu(int value);
	void createMenu();

#ifdef __cplusplus
}
#endif


#endif
