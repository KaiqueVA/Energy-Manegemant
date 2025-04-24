import { NgFor } from '@angular/common';
import { Component, Input } from '@angular/core';

@Component({
  selector: 'app-grafico-donut',
  imports: [NgFor],
  templateUrl: './grafico-donut.component.html',
  styleUrl: './grafico-donut.component.scss',
})
export class GraficoDonutComponent {
  @Input() data = [
    { label: 'Verde', value: 40, color: '#4caf50' },
    { label: 'Laranja', value: 30, color: '#ff9800' },
    { label: 'Azul', value: 30, color: '#2196f3' },
  ];

  get total() {
    return this.data.reduce((sum, item) => sum + item.value, 0);
  }

  get paths() {
    const centerX = 100;
    const centerY = 100;
    const radius = 90;
    let startAngle = 0;
    const result = [];

    for (const item of this.data) {
      const angle = (item.value / this.total) * 360;
      const endAngle = startAngle + angle;

      const start = this.polarToCartesian(centerX, centerY, radius, endAngle);
      const end = this.polarToCartesian(centerX, centerY, radius, startAngle);
      const largeArcFlag = angle > 180 ? 1 : 0;

      const pathData = [
        `M ${start.x} ${start.y}`,
        `A ${radius} ${radius} 0 ${largeArcFlag} 0 ${end.x} ${end.y}`,
        `L ${centerX} ${centerY}`,
        'Z',
      ].join(' ');

      result.push({ d: pathData, color: item.color });
      startAngle = endAngle;
    }

    return result;
  }

  polarToCartesian(cx: number, cy: number, r: number, angleDeg: number) {
    const rad = (angleDeg - 90) * (Math.PI / 180);
    return {
      x: cx + r * Math.cos(rad),
      y: cy + r * Math.sin(rad),
    };
  }
}
