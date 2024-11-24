using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;

namespace Project2
{
    public static class UtilisateurSerializer
    {
        private static string path = "C:/Travail/TP3/Database.bin";


        public static List<Utilisateur> GetUsers()
        {
            // Crée le fichier s'il n'existe pas
            if (!File.Exists(path))
            {
                FileStream myFile = File.Create(path);
                myFile.Close();
            }

            // Ouvre le fichier
            FileStream stream = new FileStream(path, FileMode.OpenOrCreate);

            // Charge la liste d'utilisateur dans le fichier
            List<Utilisateur> tempList;
            try
            {
                // Essaye de récupérer les utilisateurs
                tempList = (List<Utilisateur>)new BinaryFormatter().Deserialize(stream);
            }
            catch(SerializationException e)
            {
                // Si la liste n'existe pas, en créer une nouvelle, vide
                tempList = new List<Utilisateur>();
            }
            finally
            {
                // Ferme le fichier pour qu'on puisse y accéder ailleur
                stream.Close();
            }

            return tempList;
        }

        public static void SaveUsers(List<Utilisateur> utilisateurs)
        {
            FileStream myStream = new FileStream(path, FileMode.Create);
            new BinaryFormatter().Serialize(myStream, utilisateurs);
            myStream.Close();
        }
    }

    [Serializable]          // SerilizableAttribute
    public class Utilisateur
    {
        public string Login;
        public string Password;
        public string Email;
        public string Nom;

        public Utilisateur(string login, string password, string email, string nom)
        {
            Login = login;
            Password = password;
            Email = email;
            Nom = nom;
        }

        public Utilisateur()
        {
            Login = "";
            Password = "";
            Email = "";
            Nom = "";
        }
    }
}
