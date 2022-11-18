// portions adapted from https://github.com/exeldro/obs-downstream-keyer/

#include "dock.hpp"
#include <obs-module.h>
#include <QMainWindow>
#include <QMenu>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidgetAction>


#include "obs.hpp"
#include "plugin-macros.generated.h"

#define QT_UTF8(str) QString::fromUtf8(str)
#define QT_TO_UTF8(str) str.toUtf8().constData()

ShadowplayerDock *_dsk;

MODULE_EXPORT bool obs_module_load(void)
{
	const auto main_window =
		static_cast<QMainWindow *>(obs_frontend_get_main_window());
	obs_frontend_push_ui_translation(obs_module_get_string);
	_dsk = new ShadowplayerDock(main_window);
	obs_frontend_pop_ui_translation();
	obs_frontend_add_dock(_dsk);

	blog(LOG_INFO, "shadowplayer plugin loaded successfully (version %s)",
	     PLUGIN_VERSION);
	return true;
}

void ShadowplayerDock::frontend_save_load(obs_data_t *, bool saving,
					     void *data)
{
	auto shadowplayerDock = static_cast<ShadowplayerDock *>(data);
	if (saving) {
	    //shadowplayerDock->Save(save_data);
	} else {
		//shadowplayerDock->Load(save_data);
	    shadowplayerDock->ready = true;
	}
}

void ShadowplayerDock::frontend_event(enum obs_frontend_event ,
					 void *)
{
	//auto shadowplayerDock = static_cast<ShadowplayerDock *>(data);
	// if (event == OBS_FRONTEND_EVENT_SCENE_COLLECTION_CLEANUP &&
	//     downstreamKeyerDock->loaded) {
	// 	downstreamKeyerDock->ClearKeyers();
	// 	downstreamKeyerDock->AddDefaultKeyer();
	// } else if (event == OBS_FRONTEND_EVENT_EXIT) {
	// 	downstreamKeyerDock->ClearKeyers();
	// } else if (event == OBS_FRONTEND_EVENT_SCENE_CHANGED) {
	// 	downstreamKeyerDock->SceneChanged();
	//}
}

ShadowplayerDock::ShadowplayerDock(QWidget *parent)
	: QDockWidget(parent), ready(false)
{
	setFeatures(DockWidgetMovable | DockWidgetFloatable);
	setWindowTitle(QT_UTF8(obs_module_text("Shadowplayer")));
	setObjectName("ShadowplayerDock");
	setFloating(true);
	hide();
	tabs = new QTabWidget(this);
	tabs->setMovable(true);

	auto config = new QPushButton(this);
	config->setProperty("themeID", "configIconSmall");

	connect(config, &QAbstractButton::clicked, this,
		&ShadowplayerDock::ConfigClicked);

	tabs->setCornerWidget(config);
	setWidget(tabs);

	obs_frontend_add_save_callback(frontend_save_load, this);
	obs_frontend_add_event_callback(frontend_event, this);
}

ShadowplayerDock::~ShadowplayerDock()
{
	obs_frontend_remove_save_callback(frontend_save_load, this);
	obs_frontend_remove_event_callback(frontend_event, this);
	//ClearKeyers();
}


void ShadowplayerDock::ConfigClicked()
{
	QMenu popup;
	auto *a = popup.addAction(QT_UTF8(obs_module_text("Add")));
	connect(a, SIGNAL(triggered()), this, SLOT(Add()));
	// a = popup.addAction(QT_UTF8(obs_module_text("Rename")));
	// connect(a, SIGNAL(triggered()), this, SLOT(Rename()));
	// a = popup.addAction(QT_UTF8(obs_module_text("Remove")));
	// connect(a, SIGNAL(triggered()), this, SLOT(Remove()));
	// auto tm = popup.addMenu(QT_UTF8(obs_module_text("Transition")));
	// AddTransitionMenu(tm, transitionType::match);
	// tm = popup.addMenu(QT_UTF8(obs_module_text("ShowTransition")));
	// AddTransitionMenu(tm, transitionType::show);
	// tm = popup.addMenu(QT_UTF8(obs_module_text("HideTransition")));
	// AddTransitionMenu(tm, transitionType::hide);
	// tm = popup.addMenu(QT_UTF8(obs_module_text("ExcludeScene")));
	// AddExcludeSceneMenu(tm);
	popup.exec(QCursor::pos());
}

void ShadowplayerDock::Add()
{
	// std::string name = obs_module_text("DefaultName");
	// if (NameDialog::AskForName(this, name)) {
	// 	if (outputChannel < 7 || outputChannel >= MAX_CHANNELS)
	// 		outputChannel = 7;
	// 	auto keyer = new DownstreamKeyer(outputChannel + tabs->count(),
	// 					 QT_UTF8(name.c_str()), vendor);
	// 	tabs->addTab(keyer, keyer->objectName());
	// }
}

// void DownstreamKeyerDock::Rename()
// {
// 	int i = tabs->currentIndex();
// 	if (i < 0)
// 		return;
// 	std::string name = QT_TO_UTF8(tabs->tabText(i));
// 	if (NameDialog::AskForName(this, name)) {
// 		tabs->setTabText(i, QT_UTF8(name.c_str()));
// 	}
// }

// void DownstreamKeyerDock::Remove()
// {
// 	int i = tabs->currentIndex();
// 	if (i < 0)
// 		return;
// 	auto w = tabs->widget(i);
// 	tabs->removeTab(i);
// 	delete w;
// 	if (tabs->count() == 0) {
// 		AddDefaultKeyer();
// 	}
// }

// bool DownstreamKeyerDock::SwitchDSK(QString dskName, QString sceneName)
// {
// 	const int count = tabs->count();
// 	for (int i = 0; i < count; i++) {
// 		auto w = dynamic_cast<DownstreamKeyer *>(tabs->widget(i));
// 		if (w->objectName() == dskName) {
// 			if (w->SwitchToScene(sceneName)) {
// 				return true;
// 			}
// 		}
// 	}
// 	return false;
// }

// void DownstreamKeyerDock::RegisterObsWebsocket()
// {
// 	vendor = obs_websocket_register_vendor("downstream-keyer");
// 	if (!vendor)
// 		return;
// 	obs_websocket_vendor_register_request(vendor, "get_downstream_keyers",
// 					      get_downstream_keyers, this);
// 	obs_websocket_vendor_register_request(vendor, "dsk_select_scene",
// 					      change_scene, this);
// }

// void DownstreamKeyerDock::get_downstream_keyers(obs_data_t *request_data,
// 						obs_data_t *response_data,
// 						void *param)
// {
// 	UNUSED_PARAMETER(request_data);
// 	auto *dsk = (DownstreamKeyerDock *)param;
// 	dsk->Save(response_data);
// }

// void DownstreamKeyerDock::change_scene(obs_data_t *request_data,
// 				       obs_data_t *response_data, void *param)
// {
// 	auto *dsk = static_cast<DownstreamKeyerDock *>(param);
// 	const char *dsk_name = obs_data_get_string(request_data, "dsk_name");
// 	const char *scene_name = obs_data_get_string(request_data, "scene");
// 	if (!scene_name) {
// 		obs_data_set_string(response_data, "error", "'scene' not set");
// 		obs_data_set_bool(response_data, "success", false);
// 		return;
// 	}
// 	if (dsk_name && strlen(dsk_name)) {
// 		obs_data_set_bool(
// 			response_data, "success",
// 			dsk->SwitchDSK(QString::fromUtf8(dsk_name),
// 				       QString::fromUtf8(scene_name)));
// 		return;
// 	} else {
// 		obs_data_set_string(response_data, "error",
// 				    "'dsk_name' not set");
// 	}
// 	obs_data_set_bool(response_data, "success", false);
// }
