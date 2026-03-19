#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDial>
#include <QComboBox>
#include <QSlider>
#include <QPushButton>
#include <QFrame>
#include <QMenuBar>

class PolyOrgueStudio : public QMainWindow {
public:
    PolyOrgueStudio() {
        // --- Configuration de la fenêtre ---
        setWindowTitle("PolyOrgue Studio");
        resize(1280, 850);

        // --- 1. BARRE DE MENUS ---
        menuBar()->addMenu("Fichier");
        menuBar()->addMenu("Édition");
        menuBar()->addMenu("Instrument");
        menuBar()->addMenu("Partition");
        menuBar()->addMenu("Vues");
        menuBar()->addMenu("Aide");

        // Widget central
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        // Layout Principal horizontal
        QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

        // ==========================================================
        // 2. LEFT LAYOUT (Configuration) - Ratio 1
        // ==========================================================
        QVBoxLayout *leftLayout = new QVBoxLayout();

        leftLayout->addWidget(new QLabel("<h2>Configuration</h2>"), 0, Qt::AlignCenter);
        leftLayout->addStretch(1);

        // Section Volume
        leftLayout->addWidget(new QLabel("VOLUME PRINCIPAL"), 0, Qt::AlignCenter);

        QHBoxLayout *volumeLayout = new QHBoxLayout();
        volumeLayout->setSpacing(5); // Rapproche les labels du Dial

        QLabel *minLbl = new QLabel("Min");
        QLabel *maxLbl = new QLabel("Max");
        QDial *volumeDial = new QDial();
        volumeDial->setMinimumSize(150, 150);
        volumeDial->setNotchesVisible(true);

        volumeLayout->addStretch(); // Centre l'ensemble dans la colonne
        volumeLayout->addWidget(minLbl, 0, Qt::AlignBottom);
        volumeLayout->addWidget(volumeDial);
        volumeLayout->addWidget(maxLbl, 0, Qt::AlignBottom);
        volumeLayout->addStretch();

        leftLayout->addLayout(volumeLayout);
        leftLayout->addStretch(1);

        // Section Gammes (Centrée)
        leftLayout->addWidget(new QLabel("GAMMES"), 0, Qt::AlignCenter);
        QComboBox *gammesCombo = new QComboBox();
        gammesCombo->addItems({"Mineure", "Majeure", "Pentatonique", "Chromatique"});
        leftLayout->addWidget(gammesCombo);

        leftLayout->addStretch(1);

        // Section Sliders
        QHBoxLayout *slidersLayout = new QHBoxLayout();
        QStringList labels = {"Reverb", "Gain", "Delay", "Chorus"};
        for(const QString &txt : labels) {
            QVBoxLayout *oneSliderLayout = new QVBoxLayout();
            QSlider *s = new QSlider(Qt::Vertical);
            s->setMinimumHeight(200);
            oneSliderLayout->addWidget(s, 0, Qt::AlignCenter);
            oneSliderLayout->addWidget(new QLabel(txt), 0, Qt::AlignCenter);
            slidersLayout->addLayout(oneSliderLayout);
        }
        leftLayout->addLayout(slidersLayout);

        leftLayout->addStretch(2);

        // ==========================================================
        // 3. MIDDLE LAYOUT (Écran) - Ratio 1.5
        // ==========================================================
        QVBoxLayout *middleLayout = new QVBoxLayout();
        middleLayout->addWidget(new QLabel("<h3>Visualisation</h3>"), 0, Qt::AlignCenter);

        QFrame *ecran = new QFrame();
        ecran->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        ecran->setLineWidth(2);
        middleLayout->addWidget(ecran, 10);

        // ==========================================================
        // 4. RIGHT LAYOUT (Mapping & Accords) - Ratio 1
        // ==========================================================
        QVBoxLayout *rightLayout = new QVBoxLayout();

        // Section Mapping
        rightLayout->addWidget(new QLabel("<h2>Mapping</h2>"), 0, Qt::AlignCenter);
        rightLayout->addStretch(1);
        for(int i = 1; i <= 6; ++i) {
            QHBoxLayout *row = new QHBoxLayout();
            row->addWidget(new QLabel(QString("Touche %1 :").arg(i)));
            QLabel *noteLbl = new QLabel("DO");
            noteLbl->setFrameStyle(QFrame::Box | QFrame::Plain);
            noteLbl->setFixedWidth(45);
            noteLbl->setAlignment(Qt::AlignCenter);
            row->addWidget(noteLbl);
            row->addWidget(new QPushButton("..."));
            rightLayout->addLayout(row);
        }

        rightLayout->addStretch(1);

        // Section Banques d'accords
        rightLayout->addWidget(new QLabel("<h2>Banques d'accords</h2>"), 0, Qt::AlignCenter);
        for(int i = 1; i <= 6; ++i) {
            QHBoxLayout *row = new QHBoxLayout();
            QPushButton *playBtn = new QPushButton("▶");
            playBtn->setFixedWidth(35);
            row->addWidget(playBtn);
            row->addWidget(new QLabel(QString("Accord %1").arg(i)));
            row->addStretch();
            row->addWidget(new QPushButton("+"));
            rightLayout->addLayout(row);
        }

        rightLayout->addStretch(2);

        // ==========================================================
        // ASSEMBLAGE FINAL (Ratio 1 : 1.5 : 1)
        // ==========================================================
        mainLayout->addLayout(leftLayout, 10);
        mainLayout->addLayout(middleLayout, 15);
        mainLayout->addLayout(rightLayout, 10);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    PolyOrgueStudio w;
    w.show();
    return app.exec();
}
