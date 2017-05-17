//Anja Bühler, Lea Drießnack
//670870, 670919

using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Media.Animation;
using Microsoft.Windows.Controls;
using System.Data.SqlClient;
using System.Configuration;
using System.Data;
using System.Collections;
using System.Windows.Markup;
using System.Globalization;

namespace Manager.Tools
{

    //Funktion zum Skalieren des Bildschirms

    [ValueConversion(typeof(string), typeof(string))]
    public class RatioConverter : MarkupExtension, IValueConverter
    {
        private static RatioConverter _instance;

        public RatioConverter() { }

        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        { 
            double size = System.Convert.ToDouble(value) * System.Convert.ToDouble(parameter, CultureInfo.InvariantCulture);
            return size.ToString("G0", CultureInfo.InvariantCulture);
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return _instance ?? (_instance = new RatioConverter());
        }

    }

}

namespace Manager
{


    public partial class MainWindow : Window

    {

        SqlConnection connection = new SqlConnection(@"Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename=|DataDirectory|Datenbanken\ManagerDatabase.mdf;Integrated Security=True;Connect Timeout=30");
        SqlCommand cmd = new SqlCommand();

        int art = 0; // 0 = Filme, 1 = Spiele, 2 = Serien

        List<Film> FilmListe = new List<Film>();
        List<Film> FilmListe2 = new List<Film>();
        List<Spiel> SpielListe = new List<Spiel>();
        List<Serie> SerieListe = new List<Serie>();

        public MainWindow()
        {
            InitializeComponent();

            cmd.Connection = connection;
            connection.Open();

            for (int i = 1; i < 1000; i++)
            {
                cmd.CommandText = "SELECT * FROM FilmeTabelle WHERE id = " + i;

                SqlDataReader sqlDataReader = cmd.ExecuteReader();

                while (sqlDataReader.Read())
                {
                    Film help = new Film
                    {
                        Titel = sqlDataReader.GetString(1),
                        Beschreibung = sqlDataReader.GetString(2),
                        Erscheinungsjahr = sqlDataReader.GetInt32(3),
                        Bewertung = sqlDataReader.GetString(4),
                        Cover = sqlDataReader.GetString(5),
                        Reihe = sqlDataReader.GetString(6),
                        Gesehen = sqlDataReader.GetString(7),
                        Genre = sqlDataReader.GetString(8)
                    };
                    FilmListe.Add(help);
                }

                sqlDataReader.Close();

            }

            FilmListe.Sort(delegate (Film film1, Film film2) { return film1.Titel.CompareTo(film2.Titel); });

            connection.Close();
            listView_film.ItemsSource = FilmListe;
        }


        //boolsche Variablen, halten fest, ob entsprechendes Slidepanel gerade ein- oder ausgefahren ist

        bool neu = false;
        bool suchen = false;
        bool einstellungen = false;

        //Funktion zum Ein- bzw. Ausfahren der Slidepanel

        private void ShowHideMenu(string Storyboard, StackPanel pnl)
        {
            Storyboard sb = Resources[Storyboard] as Storyboard;
            sb.Begin(pnl);
        }


        //Onclick-Funktionen der 4 Hauptbuttons

        private void Neu_Button_Click(object sender, RoutedEventArgs e)
        {

            neumenü_groupbox.Visibility = System.Windows.Visibility.Visible;

            if (suchen == true)
            {

                ShowHideMenu("sbHideSuchenMenu", suchenmenü_panel);
                suchen = false;
            }

            if (einstellungen == true)
            {

                ShowHideMenu("sbHideEinstellungenMenu", einstellungenmenü_panel);
                einstellungen = false;
            }

            if (neu == true)
            {

                ShowHideMenu("sbHideNeuMenu", neumenü_panel);
                neu = false;
            }
            else
            {

                ShowHideMenu("sbShowNeuMenu", neumenü_panel);
                neu = true;
            }
        }

        private void Suchen_Button_Click(object sender, RoutedEventArgs e)
        {

            suchenmenü_groupbox.Visibility = System.Windows.Visibility.Visible;

            if (neu == true)
            {

                ShowHideMenu("sbHideNeuMenu", neumenü_panel);
                neu = false;

            }

            if (einstellungen == true) {

                ShowHideMenu("sbHideEinstellungenMenu", einstellungenmenü_panel);
                einstellungen = false;

            }

            if (suchen == true)
            {

                ShowHideMenu("sbHideSuchenMenu", suchenmenü_panel);
                suchen = false;
            }
            else
            {

                ShowHideMenu("sbShowSuchenMenu", suchenmenü_panel);
                suchen = true;
            }
        }

        //Starten der jeweiligen Suchen-Funktionen (siehe weiter unten) bei Klick auf den Suchen-Button

        private void suchen_starten_button_Click(object sender, RoutedEventArgs e)
        {

            ShowHideMenu("sbHideSuchenMenu", suchenmenü_panel);
            suchen = false;

            if (art == 0)
            {
                suchen_filme();
            }

            else if (art == 1)
            {
                suchen_spiele();
            }

            else
            {
                suchen_serien();
            }

            suchen_textbox.Text = null;
        }

        private void Zufall_Button_Click(object sender, RoutedEventArgs e)
        {

            if (neu == true)
            {

                ShowHideMenu("sbHideNeuMenu", neumenü_panel);
                neu = false;

            }

            if (einstellungen == true)
            {

                ShowHideMenu("sbHideEinstellungenMenu", einstellungenmenü_panel);
                einstellungen = false;

            }

            if (suchen == true)
            {

                ShowHideMenu("sbHideSuchenMenu", suchenmenü_panel);
                suchen = false;
            }

            Random random = new Random();
            ArrayList array = new ArrayList();
            cmd.Connection = connection;
            connection.Open();

            for (int i = 1; i < 1000; i++)
            {
                if (art == 0)
                {
                    cmd.CommandText = "SELECT * FROM FilmeTabelle";
                }

                else if (art == 1)
                {
                    cmd.CommandText = "SELECT * FROM SpieleTabelle";
                }

                else
                {
                    cmd.CommandText = "SELECT * FROM SerienTabelle";
                }

                SqlDataReader sqlDataReader = cmd.ExecuteReader();

                while (sqlDataReader.Read())
                {
                    array.Add(sqlDataReader.GetInt32(0));
                }

                sqlDataReader.Close();

            }

            connection.Close();

            int random_number = random.Next(array.Count);

            if (art == 0)
            {
                readDB_filme((int)array[random_number]);
            }

            else if (art == 1)
            {
                readDB_spiele((int)array[random_number]);
            }

            else
            {
                readDB_serien((int)array[random_number]);
            }

        }

        private void Einstellungen_Button_Click(object sender, RoutedEventArgs e)
        {

            einstellungenmenü_groupbox.Visibility = System.Windows.Visibility.Visible;

            if (neu == true)
            {

                ShowHideMenu("sbHideNeuMenu", neumenü_panel);
                neu = false;

            }

            if (suchen == true)
            {

                ShowHideMenu("sbHideSuchenMenu", suchenmenü_panel);
                suchen = false;
            }

            if(einstellungen == true)
            {
                ShowHideMenu("sbHideEinstellungenMenu", einstellungenmenü_panel);
                einstellungen = false;

            }
            else
            {

                ShowHideMenu("sbShowEinstellungenMenu", einstellungenmenü_panel);
                einstellungen = true;
            }
        }

        //Bestätigung der Einstellungen (noch nicht implementierte Funktionalität)

        private void Einstellungen_OK_button_Click(object sender, RoutedEventArgs e)
        {

            string text = "Diese Funktionalität ist leider noch nicht verfügbar.";
            string caption = "Einstellungen ändern";
            MessageBoxButton ok_messageBox_button = MessageBoxButton.OK;

            MessageBox.Show(text, caption, ok_messageBox_button);

            ShowHideMenu("sbHideEinstellungenMenu", einstellungenmenü_panel);
            einstellungen = false;
        }


        //Öffnen der jeweiligen "Hinzufügen"-Fenster bei Klick auf jeweiligen Button (Film, Serie, Spiel)

        private void Neu_Film_Click(object sender, RoutedEventArgs e)
        {

            Manager.neu neu_film_window = new Manager.neu();

            neu_film_window.Show();
            neu_film_window.Closed += Neu_window_Closed;

            ShowHideMenu("sbHideNeuMenu", neumenü_panel);
            neu = false;
        }

        private void Neu_Serie_Click(object sender, RoutedEventArgs e)
        {
            art = 2;

            Manager.neu_Serie neu_serie_window = new Manager.neu_Serie();

            neu_serie_window.Show();
            neu_serie_window.Closed += Neu_window_Closed;

            ShowHideMenu("sbHideNeuMenu", neumenü_panel);
            neu = false;

        }

        private void Neu_Spiel_Click(object sender, RoutedEventArgs e)
        {
            art = 1;

            Manager.neu_Spiel neu_spiel_window = new Manager.neu_Spiel();

            neu_spiel_window.Show();
            neu_spiel_window.Closed += Neu_window_Closed;

            ShowHideMenu("sbHideNeuMenu", neumenü_panel);
            neu = false;
        }

        //Initialisieren des Auslesens der Datenbank nach Schließen des "Hinzufügen"-Fensters

        private void Neu_window_Closed(object sender, EventArgs e)
        {
            if (art == 0)
            {
                readDB_filme(0);
                listView_film.Visibility = System.Windows.Visibility.Visible;
                listView_spiel.Visibility = System.Windows.Visibility.Collapsed;
                listView_serie.Visibility = System.Windows.Visibility.Collapsed;

            }
            else if (art == 1)
            {
                readDB_spiele(0);
                listView_spiel.Visibility = System.Windows.Visibility.Visible;
                listView_film.Visibility = System.Windows.Visibility.Collapsed;
                listView_serie.Visibility = System.Windows.Visibility.Collapsed;

            }
            else if (art == 2)
            {
                readDB_serien(0);
                listView_serie.Visibility = System.Windows.Visibility.Visible;
                listView_film.Visibility = System.Windows.Visibility.Collapsed;
                listView_spiel.Visibility = System.Windows.Visibility.Collapsed;
            }
        }


        //Auslesen der Informationen aus der jeweiligen Datenbank-Tabelle Filme, Serien oder Spiele

        private void readDB_filme(int random_num)
        {

            cmd.Connection = connection;
            connection.Open();

            FilmListe2.Clear();
            listView_film.ItemsSource = null;

            for (int i = 1; i < 1000; i++)
            {
                bool temp = false;

                if (random_num == 0)
                {
                    cmd.CommandText = "SELECT * FROM FilmeTabelle WHERE id = " + i;
                }

                else
                {
                    cmd.CommandText = "SELECT * FROM FilmeTabelle WHERE id = " + random_num;
                    temp = true;
                }

                SqlDataReader sqlDataReader = cmd.ExecuteReader();

                while (sqlDataReader.Read())
                {
                    Film help = new Film
                    {
                        Titel = sqlDataReader.GetString(1),
                        Beschreibung = sqlDataReader.GetString(2),
                        Erscheinungsjahr = sqlDataReader.GetInt32(3),
                        Bewertung = sqlDataReader.GetString(4),
                        Cover = sqlDataReader.GetString(5),
                        Reihe = sqlDataReader.GetString(6),
                        Gesehen = sqlDataReader.GetString(7),
                        Genre = sqlDataReader.GetString(8)
                    };

                    FilmListe2.Add(help);
                }

                sqlDataReader.Close();

                if (temp == true)
                {
                    break;
                }

            }

            connection.Close();
            listView_film.ItemsSource = FilmListe2;

        }

        private void readDB_serien(int random_num)
        {

            cmd.Connection = connection;
            connection.Open();

            SerieListe.Clear();
            listView_serie.ItemsSource = null;

            for (int i = 1; i < 1000; i++)
            {
                bool bool_help = false;

                if (random_num == 0)
                {
                    cmd.CommandText = "SELECT * FROM SerienTabelle WHERE id = " + i;
                }

                else
                {
                    cmd.CommandText = "SELECT * FROM SerienTabelle WHERE id = " + random_num;
                    bool_help = true;
                }

                SqlDataReader sqlDataReader = cmd.ExecuteReader();

                while (sqlDataReader.Read())
                {
                    Serie help = new Serie
                    {
                        Titel = sqlDataReader.GetString(1),
                        Beschreibung = sqlDataReader.GetString(2),
                        Staffel = sqlDataReader.GetInt32(3),
                        Folge = sqlDataReader.GetInt32(4),
                        Erscheinungsjahr = sqlDataReader.GetInt32(5),
                        Bewertung = sqlDataReader.GetString(6),
                        Cover = sqlDataReader.GetString(7),
                        Genre = sqlDataReader.GetString(8)
                    };

                    SerieListe.Add(help);
                }

                sqlDataReader.Close();

                if (bool_help == true)
                {
                    break;
                }

            }

            connection.Close();
            listView_serie.ItemsSource = SerieListe;

        }

        private void readDB_spiele(int random_num)
        {

            cmd.Connection = connection;
            connection.Open();

            SpielListe.Clear();
            listView_spiel.ItemsSource = null;

            for (int i = 1; i < 1000; i++)
            {
                bool bool_help = false;

                if (random_num == 0)
                {
                    cmd.CommandText = "SELECT * FROM SpieleTabelle WHERE id = " + i;
                }

                else
                {
                    cmd.CommandText = "SELECT * FROM SpieleTabelle WHERE id = " + random_num;
                    bool_help = true;
                }

                SqlDataReader sqlDataReader = cmd.ExecuteReader();

                while (sqlDataReader.Read())
                {
                    Spiel help = new Spiel
                    {
                        Titel = sqlDataReader.GetString(1),
                        Beschreibung = sqlDataReader.GetString(2),
                        Bewertung = sqlDataReader.GetString(3),
                        Cover = sqlDataReader.GetString(4),
                        Reihe = sqlDataReader.GetString(5),
                        Erscheinungsjahr = sqlDataReader.GetInt32(6),
                        Gespielt = sqlDataReader.GetString(7),
                        Genre = sqlDataReader.GetString(8)
                    };

                    SpielListe.Add(help);
                }

                sqlDataReader.Close();

                if (bool_help == true)
                {
                    break;
                }

            }

            connection.Close();
            listView_spiel.ItemsSource = SpielListe;

        }


        //Wechseln der Anzeige zwischen Filmen, Serien oder Spielen

        private void Filme_Button_sort_Click(object sender, RoutedEventArgs e)
        {
            art = 0;

            if (listView_film.Visibility == System.Windows.Visibility.Collapsed)
            {

                if (listView_serie.Visibility == System.Windows.Visibility.Visible)
                {

                    listView_serie.Visibility = System.Windows.Visibility.Collapsed;

                }
                else if (listView_spiel.Visibility == System.Windows.Visibility.Visible)
                {

                    listView_spiel.Visibility = System.Windows.Visibility.Collapsed;

                }

                listView_film.Visibility = System.Windows.Visibility.Visible;

            }

            readDB_filme(0);
        }

        private void Serien_Button_sort_Click(object sender, RoutedEventArgs e)
        {
            art = 2;

            if (listView_serie.Visibility == System.Windows.Visibility.Collapsed)
            {

                if (listView_film.Visibility == System.Windows.Visibility.Visible)
                {

                    listView_film.Visibility = System.Windows.Visibility.Collapsed;

                }
                else if (listView_spiel.Visibility == System.Windows.Visibility.Visible)
                {

                    listView_spiel.Visibility = System.Windows.Visibility.Collapsed;

                }

                listView_serie.Visibility = System.Windows.Visibility.Visible;

            }

            readDB_serien(0);
        }

        private void Spiele_Button_sort_Click(object sender, RoutedEventArgs e)
        {
            art = 1;

            if (listView_spiel.Visibility == System.Windows.Visibility.Collapsed)
            {

                if (listView_film.Visibility == System.Windows.Visibility.Visible)
                {

                    listView_film.Visibility = System.Windows.Visibility.Collapsed;

                }
                else if (listView_serie.Visibility == System.Windows.Visibility.Visible)
                {

                    listView_serie.Visibility = System.Windows.Visibility.Collapsed;

                }

                listView_spiel.Visibility = System.Windows.Visibility.Visible;

            }

            readDB_spiele(0);
        }


        //Die Suchen-Funktionen des jeweiligen Datentyps

        private void suchen_filme()
        {
            FilmListe2.Clear();
            listView_film.ItemsSource = null;

            cmd.Connection = connection;
            connection.Open();

            cmd.CommandText = "SELECT * FROM FilmeTabelle WHERE Titel LIKE '%" + suchen_textbox.Text + "%' OR Beschreibung LIKE '%" + suchen_textbox.Text + "%' OR Reihe LIKE '%" + suchen_textbox.Text + "%' OR Genre LIKE '%" + suchen_textbox.Text + "%'";

            SqlDataReader sqlDataReader = cmd.ExecuteReader();

            while (sqlDataReader.Read())
            {
                Film help = new Film
                {
                    Titel = sqlDataReader.GetString(1),
                    Beschreibung = sqlDataReader.GetString(2),
                    Erscheinungsjahr = sqlDataReader.GetInt32(3),
                    Bewertung = sqlDataReader.GetString(4),
                    Cover = sqlDataReader.GetString(5),
                    Reihe = sqlDataReader.GetString(6),
                    Gesehen = sqlDataReader.GetString(7),
                    Genre = sqlDataReader.GetString(8)
                };

                FilmListe2.Add(help);
            }
            sqlDataReader.Close();

            connection.Close();
            listView_film.ItemsSource = FilmListe2;
        }

        private void suchen_spiele()
        {
            SpielListe.Clear();
            listView_spiel.ItemsSource = null;

            cmd.Connection = connection;
            connection.Open();

            cmd.CommandText = "SELECT * FROM SpieleTabelle WHERE Titel LIKE '%" + suchen_textbox.Text + "%' OR Beschreibung LIKE '%" + suchen_textbox.Text + "%' OR Reihe LIKE '%" + suchen_textbox.Text + "%' OR Genre LIKE '%" + suchen_textbox.Text + "%'";

            SqlDataReader sqlDataReader = cmd.ExecuteReader();

            while (sqlDataReader.Read())
            {
                Spiel help = new Spiel
                {
                    Titel = sqlDataReader.GetString(1),
                    Beschreibung = sqlDataReader.GetString(2),
                    Bewertung = sqlDataReader.GetString(3),
                    Cover = sqlDataReader.GetString(4),
                    Reihe = sqlDataReader.GetString(5),
                    Erscheinungsjahr = sqlDataReader.GetInt32(6),
                    Gespielt = sqlDataReader.GetString(7),
                    Genre = sqlDataReader.GetString(8)
                };

                SpielListe.Add(help);
            }
            sqlDataReader.Close();

            connection.Close();
            listView_spiel.ItemsSource = SpielListe;
        }

        private void suchen_serien()
        {
            SerieListe.Clear();
            listView_serie.ItemsSource = null;

            cmd.Connection = connection;
            connection.Open();

            cmd.CommandText = "SELECT * FROM SerienTabelle WHERE Titel LIKE '%" + suchen_textbox.Text + "%' OR Beschreibung LIKE '%" + suchen_textbox.Text + "%' OR Genre LIKE '%" + suchen_textbox.Text + "%'";

            SqlDataReader sqlDataReader = cmd.ExecuteReader();

            while (sqlDataReader.Read())
            {
                Serie help = new Serie
                {
                    Titel = sqlDataReader.GetString(1),
                    Beschreibung = sqlDataReader.GetString(2),
                    Staffel = sqlDataReader.GetInt32(3),
                    Folge = sqlDataReader.GetInt32(4),
                    Erscheinungsjahr = sqlDataReader.GetInt32(5),
                    Bewertung = sqlDataReader.GetString(6),
                    Cover = sqlDataReader.GetString(7),
                    Genre = sqlDataReader.GetString(8)
                };

                SerieListe.Add(help);
            }
            sqlDataReader.Close();

            connection.Close();
            listView_serie.ItemsSource = SerieListe;
        }


        //Funktionen der 3 Sortieren-Buttons

        private void Az_Button_sort_Click(object sender, RoutedEventArgs e)
        {
            if (art == 0)
            {
                readDB_filme(0);
                FilmListe2.Sort(delegate (Film film1, Film film2) { return film1.Titel.CompareTo(film2.Titel); });
            }

            else if (art == 1)
            {
                readDB_spiele(0);
                SpielListe.Sort(delegate (Spiel spiel1, Spiel spiel2) { return spiel1.Titel.CompareTo(spiel2.Titel); });
            }

            else
            {
                readDB_serien(0);
                SerieListe.Sort(delegate (Serie serie1, Serie serie2) { return serie1.Titel.CompareTo(serie2.Titel); });
            }
        }

        private void Genre_Button_sort_Click(object sender, RoutedEventArgs e)
        {
            if (art == 0)
            {
                readDB_filme(0);
                FilmListe2.Sort(delegate (Film film1, Film film2) { return film1.Genre.CompareTo(film2.Genre); });
            }

            else if (art == 1)
            {
                readDB_spiele(0);
                SpielListe.Sort(delegate (Spiel spiel1, Spiel spiel2) { return spiel1.Genre.CompareTo(spiel2.Genre); });
            }

            else
            {
                readDB_serien(0);
                SerieListe.Sort(delegate (Serie serie1, Serie serie2) { return serie1.Genre.CompareTo(serie2.Genre); });
            }

        }

        private void Bewertung_Button_sort_Click(object sender, RoutedEventArgs e)
        {
            if (art == 0)
            {
                readDB_filme(0);
                FilmListe2.Sort(delegate (Film film1, Film film2) { return film2.Bewertung.CompareTo(film1.Bewertung); });
            }

            else if (art == 1)
            {
                readDB_spiele(0);
                SpielListe.Sort(delegate (Spiel spiel1, Spiel spiel2) { return spiel1.Bewertung.CompareTo(spiel2.Bewertung); });
            }

            else
            {
                readDB_serien(0);
                SerieListe.Sort(delegate (Serie serie1, Serie serie2) { return serie1.Bewertung.CompareTo(serie2.Bewertung); });
            }

        }

        



        //Anzeigen von Message-Boxen für noch nicht implementierte Funktionalitäten

        private void Bild_Button_sort_Click(object sender, RoutedEventArgs e)
        {

            string text = "Diese Funktionalität ist leider noch nicht verfügbar.";
            string caption = "In die Bildansicht wechseln";
            MessageBoxButton ok_messageBox_button = MessageBoxButton.OK;

            MessageBox.Show(text, caption, ok_messageBox_button);

        }

        private void Loeschen_Button_Click(object sender, RoutedEventArgs e)
        {

            string text = "Diese Funktionalität ist leider noch nicht verfügbar.";
            string caption = "Einträge löschen";
            MessageBoxButton ok_messageBox_button = MessageBoxButton.OK;

            MessageBox.Show(text, caption, ok_messageBox_button);

        }
}

    //Klassen für jeden Datentyp, mit jeweiligen (möglich einzugebenden) Informationen als Mitgliedsvariablen

    public class Film
    {

        public String Titel { get; set; }
        public int Erscheinungsjahr { get; set; }
        public String Beschreibung { get; set; }
        public String Bewertung { get; set; }
        public String Cover { get; set; }
        public String Reihe { get; set; }
        public String Gesehen { get; set; }
        public String Genre { get; set; }
    }

    public class Spiel
    {

        public String Titel { get; set; }
        public int Erscheinungsjahr { get; set; }
        public String Beschreibung { get; set; }
        public String Bewertung { get; set; }
        public String Cover { get; set; }
        public String Reihe { get; set; }
        public String Gespielt { get; set; }
        public String Genre { get; set; }
    }

    public class Serie
    {

        public String Titel { get; set; }
        public String Beschreibung { get; set; }
        public int Staffel { get; set; }
        public int Folge { get; set; }
        public int Erscheinungsjahr { get; set; }
        public String Bewertung { get; set; }
        public String Cover { get; set; }
        public String Genre { get; set; }
    }

}
