package projectutils;

import blockchain.BlockChain;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonElement;
import com.google.gson.JsonParser;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Reader;

public class BCJsonUtil {

    public static BlockChain BCJsonReader(String filename) {

        Gson gson = new Gson();

        try (Reader reader = new FileReader(filename)) {

            // Convert JSON to Java Object
            //System.out.println(bc);
            return gson.fromJson(reader, BlockChain.class);

            // Convert JSON to JsonElement, and later to String
            /*JsonElement json = gson.fromJson(reader, JsonElement.class);
            String jsonInString = gson.toJson(json);
            System.out.println(jsonInString);*/

        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    public static void BCJsonWriter(BlockChain BlockC, String filename){
        // JSON Parser
        //1. Convert object to JSON string
        Gson gson = new GsonBuilder().disableHtmlEscaping().setPrettyPrinting().create();
        //PrettyPrinting formatte le Json pour le rendre lisible
        JsonParser jp = new JsonParser();
        String json = gson.toJson(BlockC);
        JsonElement je = jp.parse(json);
        System.out.println(je);

        //2. Convert object to JSON string and save into a file directly
        try (FileWriter writer = new FileWriter(filename)) {
            gson.toJson(je, writer);
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

}
