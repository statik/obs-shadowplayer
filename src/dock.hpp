#pragma once
#include <QDockWidget>
#include <qmenu.h>
#include <QTabWidget>
#include <QVBoxLayout>
#include <obs-frontend-api.h>

class ShadowplayerDock : public QDockWidget {
	Q_OBJECT
private:
	bool ready;
    QTabWidget *tabs;

	static void frontend_event(enum obs_frontend_event event, void *data);
	static void change_scene(obs_data_t *request_data,
				 obs_data_t *response_data, void *param);
	static void frontend_save_load(obs_data_t *save_data, bool saving,
				       void *data);

	// void Save(obs_data_t *data);
	// void Load(obs_data_t *data);
	void ConfigClicked();
private slots:
	void Add();
// 	void Rename();
// 	void Remove();

public:
	ShadowplayerDock(QWidget *parent = nullptr);
	~ShadowplayerDock();
	void RegisterObsWebsocket();
};
