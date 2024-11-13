using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MathUI.ViewModels.LeftSide
{
    public class LeftSideViewModel : ViewModelBase
    {
        private string _shape;
        public string Shape
        {
            get => _shape;
            set => Set(ref _shape, value);
        }

        private double _positionX;
        public double PositionX
        {
            get => _positionX;
            set => Set(ref _positionX, value);
        }

        private double _positionY;
        public double PositionY
        {
            get => _positionY;
            set => Set(ref _positionY, value);
        }

        private double _radius;
        public double Radius
        {
            get => _radius;
            set => Set(ref _radius, value);
        }
    }
}
