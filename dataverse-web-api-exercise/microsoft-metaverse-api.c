using System;
using System.Net.Http;
using System.Threading.Tasks;
using Microsoft.Identity.Client;

namespace OAuthMessageHandlerSample
{
    class Program
    {
        static void Main(string[] args)
        {
            // Create the OAuthMessageHandler object.
            OAuthMessageHandler messageHandler = new OAuthMessageHandler(
                "https://yourenvname.api.crm.dynamics.com",
                "51f81489-12ee-4a9e-aaae-a2591f45987d",
                "http://localhost:8080",
                "",
                "");

            // Create the HttpClient object.
            HttpClient client = new HttpClient(messageHandler);

            // Make the request.
            var response = await client.GetAsync("WhoAmI");

            // Check the status code.
            if (response.IsSuccessStatusCode)
            {
                // Get the response content and parse it.
                JObject body = JObject.Parse(response.Content.ReadAsStringAsync().Result);

                // Get the user ID.
                Guid userId = (Guid)body["UserId"];

                // Print the user ID.
                Console.WriteLine("Your UserId is {0}", userId);
            }
            else
            {
                // Print the error message.
                Console.WriteLine("The request failed with a status of '{0}'",
                    response.ReasonPhrase);
            }

            // Wait for the user to press a key.
            Console.ReadLine();
        }
    }
}
