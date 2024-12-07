using Geometry;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

namespace MathUI.Models
{
    public class EntityModel
    {
        [JsonPropertyName("type")]
        public string Type { get; set; }

        [JsonPropertyName("scale")]
        public Scale3d Scale { get; set; } = new Scale3d();

        [JsonPropertyName("position")]
        public Point3d Position { get; set; } = new Point3d();

        [JsonPropertyName("xDir")]
        public Vector3d XDir { get; set; } = new Vector3d();

        [JsonPropertyName("yDir")]
        public Vector3d YDir { get; set; } = new Vector3d();

        [JsonPropertyName("zDir")]
        public Vector3d ZDir { get; set; } = new Vector3d();

        [JsonPropertyName("extents")]
        public Extents3d Extents { get; set; } = new Extents3d();

        public string ToJson()
        {
            return JsonSerializer.Serialize(this, new JsonSerializerOptions { WriteIndented = true });
        }

        // Deserialize JSON to the object
        public static EntityModel? FromJson(string json)
        {
            return JsonSerializer.Deserialize<EntityModel>(json);
        }
    }

}
