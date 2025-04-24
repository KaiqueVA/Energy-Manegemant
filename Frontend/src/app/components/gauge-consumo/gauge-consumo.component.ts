import { Component, Input } from '@angular/core';

@Component({
  selector: 'app-gauge-consumo',
  imports: [],
  templateUrl: './gauge-consumo.component.html',
  styleUrl: './gauge-consumo.component.scss',
})
export class GaugeConsumoComponent {
  @Input() value = 0;
  @Input() min = 0;
  @Input() max = 10;
  @Input() units = 'kWh';

  // Calcula o ângulo para o ponteiro (-90° a +90°)
  get angle(): number {
    const percent = (this.value - this.min) / (this.max - this.min);
    return -90 + percent * 90;
  }

  // Coordenadas do ponteiro
  get pointerX(): number {
    return 100 + 60 * Math.cos((this.angle * Math.PI) / 90);
  }

  get pointerY(): number {
    return 100 + 60 * Math.sin((this.angle * Math.PI) / 90);
  }

  // Arco preenchido do progresso
  // Arco preenchido do progresso
  get arcPath(): string {
    const startAngle = 180; // Ângulo de início (sempre 180º, pois o arco começa na parte inferior)
    const endAngle = 225 - this.angle; // O ângulo final é o ângulo calculado para o valor

    // Convertendo as coordenadas polares para cartesianas
    const start = this.polarToCartesian(100, 100, 90, startAngle);
    const end = this.polarToCartesian(100, 100, 90, endAngle);

    // Determinando se o arco é grande ou pequeno com base no ângulo
    const largeArcFlag = endAngle - startAngle > 180 ? 1 : 0;

    // Retorna o caminho SVG do arco
    return `M ${start.x} ${start.y}
          A 90 90 0 ${largeArcFlag} 1 ${end.x} ${end.y}`;
  }

  private polarToCartesian(
    cx: number,
    cy: number,
    r: number,
    angleDeg: number
  ) {
    const angleRad = (angleDeg * Math.PI) / 180;
    return {
      x: cx + r * Math.cos(angleRad),
      y: cy + r * Math.sin(angleRad),
    };
  }
}
