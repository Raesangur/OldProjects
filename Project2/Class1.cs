using System;
using System.Collections.Generic;
using System.Diagnostics.Eventing.Reader;
using System.Text;
using System.Threading.Tasks;

namespace Project2
{
    class Class1
    {
        protected void Login_Click(object sender, EventArgs e)
        {
            List<Utilisateur> utilisateurs = GetUsers();
            // Vérifier que le Login entré existe dans la base donnée
            // Vérifier que le mot de passe entré correspond au mot de passe de l'utilisateur

            // Enregistrer dans le dictionnaire
            Session["Login"] = TextBox1.Text;      // Login
            Session["Password"] = TextBox2.Text;   // Password

            // Rediriger vers une autre page
        }


        protected void inscription_Click(object sender, EventArgs a)
        {
            string login = Textlogin.Text;
            string pwd = Textpass.Text;
            string email = Textemail.Text;
            string nom = Textnom.Text;

            // Charge la liste d'utilisateur
            List<Utilisateur> utilisateurs = UtilisateurSerializer.GetUsers();

            // Ajoute un nouvel utilisateur
            utilisateurs.Add(new Utilisateur(login, pwd, email, nom));

            // Enregistre la liste avec les modifications
            UtilisateurSerializer.SaveUsers(utilisateurs);
        }
    }
}
